#include "MazeManager.h"
#include "Maze.h"

CMazeManager* CMazeManager::mInst = nullptr;

CMazeManager::CMazeManager()
{
}

CMazeManager::~CMazeManager()
{
    if (nullptr != mMazeArray)
    {
        for (int i = 0; i < mMazeCount;i++)
            SAFE_DELETE(mMazeArray[i]);
        delete[] mMazeArray;
    }
}

int CMazeManager::Menu()
{
    system("cls");

    for (int i = 0; i < mMazeCount; ++i)
    {
        std::cout << i + 1 << ". " <<
            mMazeArray[i]->GetName() << std::endl;
    }

    std::cout << mMazeCount + 1 << ". Back" << std::endl;
    std::cout << "Select Menu: ";
    int	Input;
    std::cin >> Input;

    if (Input < 1 || Input > mMazeCount + 1)
        return 0;

    return Input;
}

bool CMazeManager::Init()
{
    FILE* File = nullptr;
    fopen_s(&File, "MazeList.txt", "rt");
    
    if (!File)
        return false;

    char Line[MAX_STRING] = {};
    
    fgets(Line, MAX_STRING, File);

    mMazeCount = atoi(Line);

    mMazeArray = new CMaze * [mMazeCount];

    for (int i = 0;i < mMazeCount;i++)
    {
        fgets(Line, MAX_STRING, File);
        int Length = strlen(Line);

        if (Line[Length - 1] == '\n')
            Line[Length - 1] = 0;

        mMazeArray[i] = new CMaze;
        mMazeArray[i]->Init(Line);
    }
    fclose(File);
    return true;
}

void CMazeManager::Run()
{
    while (true)
    {
        int Input = Menu();

        if (Input == 0)
            continue;

        else if (Input == mMazeCount + 1)
            break;

        int Index = Input - 1;
        mMazeArray[Index]->Run();

        //__int64 Time = mMazeArray[Index]->GetTime();

    }
}
