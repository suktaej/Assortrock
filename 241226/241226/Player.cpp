#include "Player.h"
#include "ObjectManager.h"
//#include "Map.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    mPos.Y = 15;
    mPos.X = 7;
	return true;
}

void CPlayer::Update()
{


    if (_kbhit() > 0)
    {
        int Key = _getch();

        if (Key == (int)EKey::MoveKey)
        {
            Key = _getch();

            switch ((EKey)Key)
            {
            case EKey::Up:
                break;
            case EKey::Down:
                break;
            case EKey::Left:
                --mPos.X;
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
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    std::cout << "P";
}
