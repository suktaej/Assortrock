#include "Maze.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
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

    char Line[MAX_STRING] = {};
    fgets(Line, MAX_STRING, File);

    //미로 배열 크기 분할
    char* Context = nullptr;
    char* Result = nullptr;
    Result = strtok_s(Line, ", ", &Context);

    mXsize = atoi(Result);
    mYsize = atoi(Context);

    mMazeArray = new ETileType * [mYsize];
    for (int i = 0;i < mYsize;i++)
    {
        mMazeArray[i] = new ETileType[mXsize];
        fgets(Line, MAX_STRING, File);

        for (int j = 0;j < mXsize;j++)
            mMazeArray[i][j] = (ETileType)(Line[j] - '0');
    }
    
    fclose(File);
    return true;
}

void CMaze::Output()
{
    system("cls");
    for (int i = 0;i < mYsize;i++)
    {
        for (int j = 0;j < mXsize;j++)
        {
            switch (mMazeArray[i][j])
            {
            case ETileType::Road:
                std::cout << " ";
                break;
            case ETileType::Wall:
                std::cout << "#";
                break;
            case ETileType::Start:
                std::cout << "S";
                break;
            case ETileType::Goal:
                std::cout << "G";
                break;
            }
        }
        std::cout << std::endl;
    }
    system("pause");
}

void CMaze::HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // 현재 커서 정보 가져오기
    cursorInfo.bVisible = FALSE;                     // 커서를 숨김
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // 커서 정보 설정
}
