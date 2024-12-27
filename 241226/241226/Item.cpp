#include "Item.h"
#include "StageManager.h"

CItem::CItem()
{
    mType = EObjectType::Item;
}

CItem::~CItem()
{
}

bool CItem::Init()
{
	return true;
}

void CItem::Update(float DeltaTime)
{
    mMoveY += DeltaTime * 6.f;

    if (mMoveY >= 1.f)
    {
        mMoveY -= 1.f;
        ++mPos.Y;

        int CountY = CStageManager::GetInst()->GetStage()->GetStageCountY();

        if (mPos.Y >= CountY - 1)
            mActive = false;
    }
}

void CItem::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '?';
}

ECollisionType CItem::CollisionEnable(CObject* Dest)
{
    if (Dest->GetType() == EObjectType::Player)
    {
        return ECollisionType::Score;
        return ECollisionType::Heal;
    }

    return ECollisionType::None;
}
