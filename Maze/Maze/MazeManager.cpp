#include "MazeManager.h"
#include "Maze.h"

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
}
