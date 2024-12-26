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
    mPos.Y = 13;
    mPos.X = 7;
	return true;
}

void CPlayer::Update(float DeltaTime)
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
				if (mPos.X < 1)
					mPos.X = 1;
				break;
			case EKey::Right:
				++mPos.X;
				if (mPos.X > 13)
                    mPos.X = 13;
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
