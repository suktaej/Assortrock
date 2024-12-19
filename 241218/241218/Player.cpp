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
            case Ekey::Up:
                --mPos.Y;
                if (mPos.Y < 0)
                    mPos.Y = 0;
                break;
            case Ekey::Down:
                ++mPos.Y;
                break;
            case Ekey::Left:
                --mPos.X;
                if (mPos.X < 0)
                    mPos.X = 0;
                break;
            case Ekey::Right:
                ++mPos.X;
                break;
            }
        }
    }
}

void CPlayer::Output()
{
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
        std::cout << "P";

}
