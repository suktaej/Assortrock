#include "MonsterHitboxObj.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Animation/Animation2D.h"

CMonsterHitboxObj::CMonsterHitboxObj()
{
}

CMonsterHitboxObj::CMonsterHitboxObj(const CMonsterHitboxObj& Obj)
{
}

CMonsterHitboxObj::CMonsterHitboxObj(CMonsterHitboxObj&& Obj)
{
}

CMonsterHitboxObj::~CMonsterHitboxObj()
{
}

bool CMonsterHitboxObj::Init()
{
    mBody = CreateComponent<CColliderAABB2D>();

    SetRootComponent(mBody);

    //???ColliderBase�� ���������Լ��� �߰�
    //BoxSize�� ȣ�� �� �ݵ�� ������
    mBody->SetBoxSize(100.f, 100.f);
    mBody->SetPivot(0.5f, 0.5f);
    mBody->SetCollisionProfile("MonsterAttack");
    mBody->SetCollisionBeginFunc<CMonsterHitboxObj>(this, &CMonsterHitboxObj::CollisionAttack);

    SetLifeTime(1.f);
    SetDamage(1.f);

    return true;
}

void CMonsterHitboxObj::Update(float DeltaTime)
{
    CHitboxObj::Update(DeltaTime);
}

void CMonsterHitboxObj::CollisionAttack(const FVector3D& HitPoint, CColliderBase* Dest)
{
    Dest->GetOwner()->Damage(mDamage, this);

    //Effect �߰� ����
    //CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

    //Effect->SetAnimation("Explosion");

    //Effect->SetWorldPos(HitPoint);
    //Effect->SetWorldScale(20.f, 20.f);

    Destroy();
}
