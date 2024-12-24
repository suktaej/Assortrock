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

    return true;
}

void CMaze::Output()
{
}
