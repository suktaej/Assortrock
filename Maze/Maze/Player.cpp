#include "Player.h"

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
                if (mPos.Y < 0)
                    mPos.Y = 0;
                break;
            case EKey::Down:
                ++mPos.Y;
                break;
            case EKey::Left:
                --mPos.X;
                if (mPos.X < 0)
                    mPos.X = 0;
                break;
            case EKey::Right:
                ++mPos.X;
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
