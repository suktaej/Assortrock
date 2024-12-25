#include "Maze.h"
#include "Player.h"

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

    //�̷� �迭 ũ�� ����
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

void CMaze::Run()
{
    system("cls");

    CPlayer* Player = new CPlayer;
    //player �����Ҵ�, ���� ����
    Player->Init();
    Player->SetPos(mStartPos);
    //�÷��̾� ���������� ��ŸƮ������ ������ ��ǥ
    Player->SetMaze(this);
    //��ü �ڽ��� �ּҰ��� �Ѱ��ش�...

    while (true)
    {
        Player->Update();
    }

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
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // ���� Ŀ�� ���� ��������
    cursorInfo.bVisible = FALSE;                     // Ŀ���� ����
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Ŀ�� ���� ����
}

ETileType CMaze::GetTile(int x, int y) const
{
    if (x < 0 || x >= mXsize || y < 0 || y >= mYsize)
        return ETileType::Wall;
    return mMazeArray[y][x];
}
