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
    if (_kbhit())
    {
        int Key = _getch();
        //ó�� �޾ƿ��� ���� �Ϲ�Ű(a,s,d...)�� �ƴ� Ư��Ű�� ���
        //������ ��(left, right�� �ƴ� Movekey)�� ��ȯ
        if (Key == (int)EKey::MoveKey)
        {
            Key = _getch();
            //�� ��° ȣ�� �� ����Ű ���� ��ȯ
            switch ((EKey)Key)
            {
            case EKey::Up:
                --mPos.Y;
                if (mMaze->GetTile(mPos.X,mPos.Y) == ETileType::Wall)
                    ++mPos.Y;
                break;
            case EKey::Down:
                ++mPos.Y;
                if (mMaze->GetTile(mPos.X,mPos.Y) == ETileType::Wall)
                    --mPos.Y;
                break;
            case EKey::Left:
                --mPos.X;
                if (mMaze->GetTile(mPos.X,mPos.Y) == ETileType::Wall)
                    ++mPos.X;
                break;
            case EKey::Right:
                ++mPos.X;
                if (mMaze->GetTile(mPos.X,mPos.Y) == ETileType::Wall)
                    --mPos.X;
                break;
            }
        }

    }
}

void CPlayer::Output()
{
}

void CPlayer::Output(char* OutBuffer, int CountX)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    std::cout << "P";
}
