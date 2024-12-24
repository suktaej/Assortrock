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
        //처음 받아오는 값은 일반키(a,s,d...)가 아닌 특수키인 경우
        //별도의 값(left, right가 아닌 Movekey)이 반환
        if (Key == (int)EKey::MoveKey)
        {
            Key = _getch();
            //두 번째 호출 시 방향키 값을 반환
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
