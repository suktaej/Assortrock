#include "Object.h"
#include "StageManager.h"
#include "Stage.h"

FObject::FObject()
{
}

FObject::~FObject()
{
}

void FObject::SetLock()
{
	mMoveY = 0; 
	mMoveX = 0; 
	mPlaced = true;
    FStageManager::GetInst()->GetStage();
}

void FObject::Update(float DeltaTime)
{
    //키조작
    if (_kbhit() > 0)
    {
        int Key = _getch();

        if ((EKey)Key == EKey::MoveKey)
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
                if (mPos.X > FStageManager::GetInst()->GetStage()->GetXsize()-2)
                    mPos.X = FStageManager::GetInst()->GetStage()->GetXsize()-2;
                break;
            }
        }
    }
    
    //자동이동
	mMoveY += DeltaTime * 4;
	int Floor = FStageManager::GetInst()->GetStage()->GetYsize();

	if (mMoveY >= 1.f)
	{
		mMoveY -= 1.f;
		mPos.Y++;
        
        //바닥과 충돌 시 정지
		if (mPos.Y == Floor - 7)
		{
			SetLock();
			FStageManager::GetInst()->GetStage()->SetActive();
		}
	}

    //객체 간 충돌
}
