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
        for (int i = 0; i < mYsize; i++)
            delete[] mMazeArray[i];
        delete[] mMazeArray;
    }

    if (nullptr != mOutputBuffer)
        delete[]mOutputBuffer;
}

bool CMaze::Init()
{
    return true;
}

bool CMaze::Init(const char* FileName)
{
    FILE* File = nullptr;
    fopen_s(&File, FileName, "rt");

    if (!File)
        return false;

    strcpy_s(mName, FileName);
    
    char Line[MAX_STRING] = {};
    fgets(Line, MAX_STRING, File);

    //미로 배열 크기 분할
    char* Context = nullptr;
    char* Result = nullptr;
    Result = strtok_s(Line, ", ", &Context);

    mXsize = atoi(Result);
    mYsize = atoi(Context);

    mOutputBuffer = new char[(mXsize + 1) * mYsize + 1];
    memset(mOutputBuffer, 0, sizeof(char) * ((mXsize + 1) * mYsize + 1));

    mMazeArray = new ETileType * [mYsize];
    for (int i = 0;i < mYsize;i++)
    {
        mMazeArray[i] = new ETileType[mXsize];
        fgets(Line, MAX_STRING, File);

        for (int j = 0; j < mXsize; j++)
        {
            int OutputBufferIndex = i * (mXsize + 1) + j;
            mMazeArray[i][j] = (ETileType)(Line[j] - '0');
            
            switch (mMazeArray[i][j])
            {
            case ETileType::Road:
                mOutputBuffer[OutputBufferIndex] = ' ';
                break;
            case ETileType::Wall:
                mOutputBuffer[OutputBufferIndex] = '#';
                break;
            case ETileType::Start:
                mOutputBuffer[OutputBufferIndex] = 'S';
                mStartPos.X = j;
                mStartPos.Y = i;
                break;
            case ETileType::Goal:
                mOutputBuffer[OutputBufferIndex] = 'G';
                mGoalPos.X = j;
                mGoalPos.Y = i;
                break;
            case ETileType::Item:
            {
                CItem* Item = new CItem;

                Item->Init();
                Item->SetPos(j, i);

                Reallocation();
                
                mObjectList[mObjectCount] = Item;
                ++mObjectCount;

                mOutputBuffer[OutputBufferIndex] = '!';
            }
                break;
            }
        }
        int LFIndex = i * (mXsize + 1) + mXsize;
        mOutputBuffer[LFIndex] = '\n';
    }
    
    fclose(File);
    return true;
}

void CMaze::Run()
{
    system("cls");

    CPlayer* Player = new CPlayer;
    
    Player->Init();
    Player->SetPos(mStartPos);
    Player->SetMaze(this);

    int StartIndex = mStartPos.Y * (mXsize + 1) + mStartPos.X;
    int GoalIndex = mGoalPos.Y * (mXsize + 1) + mGoalPos.X;
    
    mPrevPlayerIndex = StartIndex;
    mPrevPlayerOutput = 0;

    while (true)
    {
        Player->Update();
        
        COORD PlayerPos = Player->GetPos();
        int PlayerIndex = PlayerPos.Y * (mXsize + 1) + PlayerPos.X;

        for (int i = 0; i < mObjectCount; i++)
            mObjectList[i]->Update();

        for (int i = 0; i < mObjectCount; i++)
        {
            CItem* Item = dynamic_cast<CItem*>(mObjectList[i]);

            if (nullptr != Item)
            {
                if (PlayerPos.X == Item->GetPos().X &&
                    PlayerPos.Y == Item->GetPos().Y)
                {
                    //mScore += 10;
                    mOutputBuffer[PlayerIndex] = ' ';

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

        //mOutputBuffer[StartIndex] = 'S';
        //mOutputBuffer[GoalIndex] = 'G';

        for (int i = 0; i < mObjectCount; i++)
            mObjectList[i]->Output(mOutputBuffer,mXsize+1);

        if (mPrevPlayerOutput != 0)
            mOutputBuffer[mPrevPlayerIndex] = mPrevPlayerOutput;

        mPrevPlayerIndex = PlayerIndex;
        mPrevPlayerOutput = mOutputBuffer[PlayerIndex];

        mOutputBuffer[PlayerIndex] = 'P';

        COORD   Cursor = {};
        SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Cursor);

        std::cout << mOutputBuffer;

		if (GetTile(PlayerPos.X, PlayerPos.Y) == ETileType::Goal)
            break;
    }
}

void CMaze::Output()
{
}

void CMaze::Reallocation()
{
    if (mObjectCapacity == mObjectCount)
    {
        mObjectCapacity *= 2;

        CObject** Array = new CObject * [mObjectCapacity];
        memset(Array, 0, sizeof(CObject*) * mObjectCapacity);
        delete[] mObjectList;
        mObjectList = Array;
    }
}


void CMaze::HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // 현재 커서 정보 가져오기
    cursorInfo.bVisible = FALSE;                     // 커서를 숨김
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // 커서 정보 설정
}

ETileType CMaze::GetTile(int x, int y) const
{
    if (x < 0 || x >= mXsize || y < 0 || y >= mYsize)
        return ETileType::Wall;
    return mMazeArray[y][x];
}
