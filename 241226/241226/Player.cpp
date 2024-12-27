#include "Player.h"
#include "ObjectManager.h"
#include "Stage.h"
#include "Bullet.h"
#include "StageManager.h"

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
        else if (Key == (int)EKey::Fire)
        {
            CBullet* Bullet = CObjectManager::GetInst()->CreateObj<CBullet>();
            Bullet->SetPos(mPos.X, mPos.Y - 1);
            Bullet->SetMoveDir(0.f, -1.f);
        }
    }
}

void CPlayer::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = 'P';
    //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    //std::cout << "P";
}
