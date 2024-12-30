#include "Player.h"
#include "Stage.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	mPos.Y = 7;
	mPos.X = 7;

    return true;
}

void CPlayer::Update(float DeltaTime)
{
    if (_kbhit() > 0)
    {
        int Key = _getch();

        if (Key == EKey::MoveKey)
        {
            Key = _getch();

            switch (Key)
            {
            case EKey::Up:
				mDirX = 0;
				mDirY = -1;
                //--mPos.Y;
				//if (mPos.Y > 15)
				//	++mPos.Y;
				break;
			case EKey::Down:
				mDirX = 0;
				mDirY = 1;
				//++mPos.Y;
				//if (mPos.Y < 0)
				//	--mPos.Y;
				break;
			case EKey::Left:
				mDirX = -1;
				mDirY = 0;
				//--mPos.X;
				//if (mPos.X < 0)
				//	++mPos.X;
				break;
			case EKey::Right:
				mDirX = 1;
				mDirY = 0;
				//++mPos.X;
				//if (mPos.X > 15)
				//	--mPos.X;
				break;
			default:
				mDirX = 0;
				mDirY = 1;
				break;
			}
		}
	}

	int Xsize = CStage::GetInst()->GetXsize();
    int Ysize = CStage::GetInst()->GetYsize();
	
	mMove += DeltaTime * 2;

	if (mMove >= 1.f)
	{
		mMove -= 1.f;
		mPos.X += mDirX;
		mPos.Y += mDirY;

		if (mPos.X < 1 ||
			mPos.X >= Xsize - 1 ||
			mPos.Y < 1 ||
			mPos.Y >= Ysize - 1)
		{
			CStage::GetInst()->SetDeath();
			return;
		}
	}
}

void CPlayer::Output(char* Buffer)
{
	//SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), mPos);
	//std::cout << "P";
	int Xsize = 15;
	Buffer[mPos.Y * (Xsize + 1) + mPos.X] = 'P';
}
