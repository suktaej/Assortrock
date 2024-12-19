#include "Maze.h"
#include "Player.h" //player ���� �� ȣ���� ����

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
    //�迭�� ���� �����ؼ� �����̸��� ����
    //���� .�������� ������ ������ Ȯ���� ����
    char* Context = nullptr;
    char* Result = strtok_s(Buffer, ".", &Context);
    strcpy_s(mName, Result);
    //������� mName�� Ȯ���ڸ� ������ �̷��� �̸��� ����

    char Line[128] = {};
    fgets(Line, 128, File);
    //ù��° ���� �迭�� ũ��(10, 10)
    Result = strtok_s(Line, ", ", &Context);
    //', '���� �и�
    mCountX = atoi(Result);
    mCountY = atoi(Context);

    mMazeArray = new ETileType * [mCountY];
    //������ �� ��ŭ �����Ҵ�
    //cout���� �� �ܾ ����ϴ� ���� �ƴ� ���۸� ���� �迭�� �ѹ��� ����ϱ� ����
    mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];
    //������ + 1(���๮��) * ������ �� + 1(�迭�� ������ \0) ��ŭ ��¹��ۿ� �����Ҵ� 
    memset(mOutputBuffer,0,sizeof(char)*((mCountX + 1) * mCountY + 1));
    //�޸� �ʱ�ȭ �Լ�

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
            
            int OutputIndex = i * (mCountX + 1) + j;
            //1���� �迭�� ��¹����� ������ ��
            switch (mMazeArray[i][j])
            {
            case ETileType::Road:
                mOutputBuffer[OutputIndex] = ' ';
                //1���� �迭
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
        //������ ������ ���๮�� �߰�
        //������ �� �ε����� mCountX+1 ��ŭ�̹Ƿ� mCountX�� ������ �� �ε����� ��
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
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // ���� Ŀ�� ���� ��������
    cursorInfo.bVisible = FALSE;                     // Ŀ���� ����
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Ŀ�� ���� ����
}

void CMaze::Run()
{
    system("cls");
    //�÷��̾� ����
    CPlayer* Player = new CPlayer;

    Player->Init();
    Player->SetPos1(mStartPos);

    while (true)
    {
        //system("cls");
        //����� ����
        Player->Update();

        COORD Cursor = {};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
        HideCursor();
        Output();
        Player->Output();
    }
}
