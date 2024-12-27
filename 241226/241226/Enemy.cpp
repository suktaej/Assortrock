#include "Enemy.h"
#include "Stage.h"
#include "Bullet.h"
#include "StageManager.h"
#include "ObjectManager.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
    return true;
}

void CEnemy::Output(char* OutputBuffer)
{
    //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    //std::cout << "E";
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = 'V';
}

void CEnemy::Update(float DeltaTime)
{
    mMoveY += DeltaTime;
    
    if (mMoveY >= 1.f)
    {
        mMoveY -= 1.f;
        ++mPos.Y;
   
		int CountY = CStageManager::GetInst()->GetStage()->GetStageCountY();
        
        if (mPos.Y >= CountY -1)
            mActive = false;
    }
    mFireTime += DeltaTime;

    if (mFireTime >= 3.f)
    {
        mFireTime -= 3.f;

        CBullet* Bullet = CObjectManager::GetInst()->CreateObj<CBullet>();
        Bullet->SetPos(mPos.X, mPos.Y + 1);
        Bullet->SetMoveDir(0.f, 1.f);
        Bullet->SetType(EObjectType::EnemyBullet);
    }
}

ECollisionType CEnemy::CollisionEnable(CObject* Dest)
{
    switch (Dest->GetType())
    {
    case EObjectType::Player:
    case EObjectType::PlayerBullet:
        return ECollisionType::Damage;
    }
    return ECollisionType::None;
}

bool CEnemy::Damage(int Dmg)
{
	mHP -= Dmg;
	if (mHP <= 0)
		return true;
	return false;
}

