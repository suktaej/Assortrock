#include "Maze.h"
#include "Player.h" //player 생성 시 호출을 위함

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
}

bool CMaze::Init(const char* FileName)
{
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
                std::cout << "S";
                break;
            case ETileType::Goal:
                mOutputBuffer[OutputIndex] = 'G';
                std::cout << "G";
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
    //플레이어 생성
    CPlayer* Player = new CPlayer;

    Player->Init();
    Player->SetPos1(mStartPos);

    while (true)
    {
        //system("cls");
        //출력이 느림
        Player->Update();

        COORD Cursor = {};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
        HideCursor();
        Output();
        Player->Output();
    }
}
