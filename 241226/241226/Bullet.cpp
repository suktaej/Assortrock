#include "Bullet.h"
#include "StageManager.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
    return true;
}

void CBullet::Update(float DeltaTime)
{
    mMoveX += mMoveDirX * DeltaTime * 7.f;
    mMoveY += mMoveDirY * DeltaTime * 7.f;

    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    int CountY = CStageManager::GetInst()->GetStage()->GetStageCountY();

    //mMoveX�� �������� �� ��� -1���� �۰ų� ����
    //mMoveX�� ���������� �� ��� 1���� ũ�ų� ����
    //mMoveY�� �Ʒ��� �� ��� 1���� ũ�ų� ����
    //mMoveY�� ���� �� ��� 1���� �۰ų� ����
    //abs : ���밪 �Լ�
    if (abs(mMoveY) >= 1.f)
    {
        mPos.Y += (int)mMoveY;
        mMoveY -= (int)mMoveY;
        //�м��ʿ�

        if (mPos.Y < 1 || mPos.Y >= CountY-1)   //0, CountX-1�� ��(#)
            mActive = false;
        //�� �浹 ó��
    }

    if (abs(mMoveX) >= 1.f)
    {
        mPos.X += (int)mMoveX;
        mMoveX -= (int)mMoveX;
        
        if (mPos.X < 1 || mPos.X >= CountX-1)
            mActive = false;
    }

}

void CBullet::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '*';
}

ECollisionType CBullet::CollisionEnable(CObject* Dest)
{
    if (mType == EObjectType::PlayerBullet &&
        Dest->GetType() == EObjectType::Enemy)
        return ECollisionType::Damage;

    else if (mType == EObjectType::EnemyBullet &&
        Dest->GetType() == EObjectType::Player)
        return ECollisionType::Damage;
    
    return ECollisionType::None;
}
