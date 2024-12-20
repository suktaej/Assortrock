#include "Player.h"
#include "Maze.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    return true;
}

void CPlayer::Update()
{
    if (_kbhit() > 0)
        //Ű�� ������ ������ Ȯ���ϴ� �Լ�
    {
        int Key = _getch();
        if (Key == (int)Ekey::Movekey)
        {
            //Ű�� �޾ƿ� �Է°�(����)�� ��ȯ�ϴ� �Լ�
            //�ٸ� ���ڳ� ����Ű�� �޾ƿ��� �뵵�̹Ƿ� Ư��Ű�� ���������� �ν����� ���� �� ����
            Key = _getch();
            //2ȸ �޾ƿ� ��, ù��°�� ����Ű�� ���� ��ġ, �������� �޾ƿ��� ���� ��� ���������� ���� ��ġ
            switch ((Ekey)Key)
            {
                //�ʸ��� ����, ������ ũ�Ⱑ �ٸ� �� �����Ƿ� �̷��� ������ �޾ƿ� �ʿ䰡 ����
            case Ekey::Up:
                --mPos.Y;
                if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    ++mPos.Y;
                break;
            case Ekey::Down:
                ++mPos.Y;
                if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    --mPos.Y;
                break;
            case Ekey::Left:
                --mPos.X;
                if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    ++mPos.X;
                break;
            case Ekey::Right:
                ++mPos.X;
                if (mMaze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    --mPos.X;
                break;
            }
        }
    }
}

void CPlayer::Output(char* OutBuffer,int CountX)
{
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
        std::cout << "P";
}

bool CPlayer::SetHP(int Input)
{
    mHP += Input;

    if (mHP > 5)
        mHP = 5;

    return mHP <= 0;
}
