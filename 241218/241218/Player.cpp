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
        //키가 눌러진 것인지 확인하는 함수
    {
        int Key = _getch();
        if (Key == (int)Ekey::Movekey)
        {
            //키를 받아와 입력값(숫자)를 반환하는 함수
            //다만 문자나 숫자키를 받아오는 용도이므로 특수키는 정상적으로 인식하지 못할 수 있음
            Key = _getch();
            //2회 받아올 때, 첫번째는 방향키에 대한 수치, 다음으로 받아오는 것은 어느 방향인지에 대한 수치
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
