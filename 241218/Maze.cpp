#include "Maze.h"
#include "Player.h"
#include "Item.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
    if (nullptr != mMazeArray)
    {
        for (int i = 0;i < mCountY;i++)
            delete[] mMazeArray[i];
    }
    delete mMazeArray;
    //삭제 확인
    if(nullptr!=mOutputBuffer)
		delete[] mOutputBuffer;
}

bool CMaze::Init(const char* FileName)
{
    mObjectList = new CObject * [mObjectCapacity];
    //생성한 아이템, 함정 등을 저장하기 위한 오브젝트 배열

    FILE* File = nullptr;
    fopen_s(&File, FileName, "rt");

    if (!File)
        return false;

    char Buffer[128] = {};
    strcpy_s(Buffer, FileName);
    //배열을 새로 생성해서 파일이름을 복사
    //이후 .기준으로 문장을 나누어 확장자 제거
    char* Context = nullptr;
    char* Result = strtok_s(Buffer, ".", &Context);
    strcpy_s(mName, Result);
    //멤버변수 mName에 확장자를 제거한 미로의 이름을 복사

    char Line[128] = {};
    fgets(Line, 128, File);
    //첫번째 줄은 배열의 크기(10, 10)
    Result = strtok_s(Line, ", ", &Context);
    //', '기준 분리
    mCountX = atoi(Result);
    mCountY = atoi(Context);

    mMazeArray = new ETileType * [mCountY];
    //세로줄 수 만큼 동적할당
    //cout으로 한 단어씩 출력하는 것이 아닌 버퍼를 통해 배열을 한번에 출력하기 위함
    mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];
    //가로줄 + 1(개행문자) * 세로줄 수 + 1(배열의 마지막 \0) 만큼 출력버퍼에 동적할당 
    memset(mOutputBuffer,0,sizeof(char)*((mCountX + 1) * mCountY + 1));
    //메모리 초기화 함수
    mItemBackup = new COORD[mObjectCapacity];
    for (int i = 0;i < mCountY;i++)
    {
        mMazeArray[i] = new ETileType[mCountX];
        //가로줄 수 만큼 동적할당 
        fgets(Line, 128, File);
        for (int j = 0;j < mCountX;j++)
        {
            //char Number[2] = {};
            //Number[0] = Line[j];
            //mMazeArray[i][j] = (ETileType)atoi(Number);
            mMazeArray[i][j] = (ETileType)(Line[j]-'0');
            
            int OutputIndex = i * (mCountX + 1) + j;
            //1차원 배열인 출력버퍼의 세로줄 값
            switch (mMazeArray[i][j])
            {
            case ETileType::Road:
                mOutputBuffer[OutputIndex] = ' ';
                //1차원 배열
                break;
            case ETileType::Wall:
                mOutputBuffer[OutputIndex] = '#';
                break;
            case ETileType::Start:
                mStartPos.X = j;
                mStartPos.Y = i;
                mOutputBuffer[OutputIndex] = 'S';
                break;
            case ETileType::Goal:
                mGoalPos.X = j;
                mGoalPos.Y = i;
                mOutputBuffer[OutputIndex] = 'G';
                break;
            case ETileType::Item:
                //아이템 생성
                CItem* Item = new CItem;
                Item->Init();
                Item->SetPos(j, i);

                if (mObjectCount == mObjectCapacity)
                {
                    mObjectCapacity *= 2;
                    CObject** Array = new CObject * [mObjectCapacity];
                    memcpy(Array, mObjectList, sizeof(CObject*)*mObjectCount);
                    
                    COORD* BackupArray = new COORD[mObjectCapacity];
                    memcpy(BackupArray, mItemBackup, sizeof(COORD) * mItemCount);

                    delete[] mObjectList;
                    delete[] mItemBackup;
                    mObjectList = Array;
                    mItemBackup = BackupArray;
                }
                //배열 크기 재정의
                mObjectList[mObjectCount] = Item;
                mItemBackup[mItemCount] = { (short)j, (short)i };
                mObjectCount++;
                mItemCount++;

                mOutputBuffer[OutputIndex] = ' ';
                //디폴트 이미지는 길과 동일
                break;
            }

//            if (mMazeArray[i][j] == ETileType::Start)
//            {
//                mStartPos.X = j;
//                mStartPos.Y = i;
//            }
        }
        int OutputIndex = i * (mCountX + 1) + mCountX;
        mOutputBuffer[OutputIndex] = '\n';
        //한줄이 끝나면 개행문자 추가
        //가로의 끝 인덱스는 mCountX+1 만큼이므로 mCountX가 가로의 끝 인덱스가 됨
    }
    fclose(File);
    return true;
}

void CMaze::Output()
{
    
    std::cout << mOutputBuffer;
//    for (int i = 0;i < mCountY;i++)
//    {
//        for (int j = 0; j < mCountX;j++)
//        {
//            switch (mMazeArray[i][j])
//            {
//            case ETileType::Road:
//                std::cout << " ";
//                break;
//            case ETileType::Wall:
//                std::cout << "#";
//                break;
//            case ETileType::Start:
//                std::cout << "S";
//                break;
//            case ETileType::Goal:
//                std::cout << "G";
//                break;
//            }
//        }
//        std::cout << std::endl;
//    }
}

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // 현재 커서 정보 가져오기
    cursorInfo.bVisible = FALSE;                     // 커서를 숨김
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // 커서 정보 설정
}

void CMaze::Run()
{
    system("cls");
    //시간
    __int64 TimeStart = time(0);

    //플레이어 생성
    CPlayer* Player = new CPlayer;

    Player->Init();
    Player->SetPos(mStartPos);
    Player->SetMaze(this);
	//===this확인===

    int StartIndex = mStartPos.Y * (mCountX + 1) + mStartPos.X;
    int GoalIndex = mGoalPos.Y * (mCountX + 1) + mGoalPos.X;
    
    mPrevPlayerIndex = StartIndex;
    mPrevPlayerOutput = 0;
    //===+1 확인==17:54===
    //==1차원 배열 위에서의 시작지점과 도착지점의 위치

    while (true)
    {
        //system("cls");
        //출력이 느림
        Player->Update();

        //플레이어 위치 받아오기
        COORD PlayerPos = Player->GetPos();
        int PlayerIndex = PlayerPos.Y * (mCountX + 1) + PlayerPos.X;
        
        //오브젝트 업데이트
        for (int i = 0;i < mObjectCount;i++)
            mObjectList[i]->Update();
        
        for (int i = 0;i < mObjectCount;i++)
        {
            //오브젝트가 아이템인지 확인
            //1.열거형으로 오브젝트 타입을 저장
            //2.dynamic cast를 사용해 오브젝트 타입을 확인
            CItem* Item = dynamic_cast<CItem*>(mObjectList[i]);
            
            if (Item != nullptr)
            {
                if (PlayerPos.X == Item->GetPos().X &&
                    PlayerPos.Y == Item->GetPos().Y)
                {
                    mScore += 10;
                    //아이템을 먹게 되면 버퍼를 길로 변경
                    mOutputBuffer[PlayerIndex] = ' ';

                    //현재 위치의 아이템과 배열의 가장 마지막 오브젝트 위치 변경
                    //배열의 크기를 1 감소
                    //배열 마지막의 오브젝트일 경우 예외처리
                    if (i < mObjectCount - 1)
                    {
                        CObject* Temp = mObjectList[i];
                        mObjectList[i] = mObjectList[mObjectCount - 1];
                        mObjectList[mObjectCount - 1] = Temp;
                    }
                    delete mObjectList[mObjectCount - 1];
                    mObjectList[mObjectCount - 1] = nullptr;
                    --mObjectCount;
                }
            }
        }

        //시작지점과 도착지점의 출력을 버퍼를 통해 새로 생성
        mOutputBuffer[StartIndex] = 'S';
        mOutputBuffer[GoalIndex] = 'G';

        //플레이어의 이전 프레임 인덱스를 복구
        if (mPrevPlayerOutput != 0)
            mOutputBuffer[mPrevPlayerIndex] = mPrevPlayerOutput;

        mPrevPlayerIndex = PlayerIndex;
        mPrevPlayerOutput = mOutputBuffer[PlayerIndex];
        //===25:55===

        for (int i = 0; i < mObjectCount; i++)
            mObjectList[i]->Output(mOutputBuffer,mCountX+1);
        
        mOutputBuffer[PlayerIndex] = 'P';

        COORD Cursor = {};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
        //콘솔 커서의 위치를 처음으로 돌려줌
        HideCursor();
        Output();

        if (GetTile(PlayerPos.X, PlayerPos.Y) == ETileType::Goal)
            break;
        //Player->Output();

        COORD ScorePos;
        ScorePos.X = 0;
        ScorePos.Y = mCountY + 1;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
        std::cout << "Score: " << mScore;
        //스코어 출력

        __int64 Time = time(0);
        mTime = Time - TimeStart;

        COORD TimePos;
        TimePos.X = 10;
        TimePos.Y = mCountY + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TimePos);

        int Minute = mTime / 60;
        int Second = mTime % 60;
		std::cout<<"Time: "<<Minute << ":" << Second;
        //시간 출력
    }
    SAFE_DELETE(Player);
    ResetItems();
    mScore = 0;
}

ETileType CMaze::GetTile(int x, int y) const
{
    if (x < 0 || x >= mCountX ||
        y < 0 || y >= mCountY)
        return ETileType::Wall;

    return mMazeArray[y][x];
}

void CMaze::ResetItems()
{
    for (int i = 0; i < mObjectCount; i++)
        delete mObjectList[i];

    mObjectCount = 0;

    // 백업 배열을 기반으로 아이템 재생성
    for (int i = 0; i < mItemCount; i++)
    {
        CItem* Item = new CItem;
        Item->Init();
        Item->SetPos(mItemBackup[i].X, mItemBackup[i].Y);

        mObjectList[mObjectCount] = Item;
        mObjectCount++;
    }
}

