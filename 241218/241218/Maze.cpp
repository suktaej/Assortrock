#include "Maze.h"

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

    char Line[128] = {};

    fgets(Line, 128, File);
    //ù��° ���� �迭�� ũ��(10, 10)
    char* Context = nullptr;
    char* Result = strtok_s(Line, ", ", &Context);
    //', '���� �и�
    mCountX = atoi(Result);
    mCountY = atoi(Context);

    mMazeArray = new ETileType * [mCountY];
    //������ �� ��ŭ �����Ҵ�

    for (int i = 0;i < mCountY;i++)
    {
        mMazeArray[i] = new ETileType[mCountX];
        //������ �� ��ŭ �����Ҵ� 
        fgets(Line, 128, File);
        for (int j = 0;j < mCountX;j++)
        {
            //char Number[2] = {};
            //Number[0] = Line[j];
            //mMazeArray[i][j] = (ETileType)atoi(Number);
            mMazeArray[i][j] = (ETileType)(Line[j]-'0');
            //atoi ����� Ȯ��
        }
    }
    fclose(File);
    return true;
}

void CMaze::Output()
{
    for (int i = 0;i < mCountY;i++)
    {
        for (int j = 0; j < mCountX;j++)
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
}
