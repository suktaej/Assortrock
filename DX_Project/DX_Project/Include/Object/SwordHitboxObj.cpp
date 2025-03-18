#include "SwordHitBoxObj.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderOBB2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Animation/Animation2D.h"

CSwordHitboxObj::CSwordHitboxObj()
{
}

CSwordHitboxObj::CSwordHitboxObj(const CSwordHitboxObj& Obj)
{
}

CSwordHitboxObj::CSwordHitboxObj(CSwordHitboxObj&& Obj)
{
}

CSwordHitboxObj::~CSwordHitboxObj()
{
}

bool CSwordHitboxObj::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderOBB2D>();
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    SetRootComponent(mRoot);

    mRoot->SetPivot(0.5f, 0.5f);
    mRoot->SetWorldScale(28.f, 40.f, 1.f);

    mRoot->AddChild(mBody);

    //???ColliderBase에 순수가상함수로 추가
    mBody->SetBoxSize(28.f, 40.f);
    mBody->SetPivot(0.5f, 0.5f);
    mBody->SetCollisionProfile("PlayerAttack");
    mBody->SetCollisionBeginFunc<CSwordHitboxObj>(this, &CSwordHitboxObj::CollisionAttack);

    mAnimation->AddSequence("SwordAttack", 0.3f, 1.f, false, false);
    mAnimation->ChangeAnimation("SwordAttack");
    
    SetDamage(1.f);
    SetLifeTime(0.3f);
   
    return true;
}

void CSwordHitboxObj::Update(float DeltaTime)
{
    CHitboxObj::Update(DeltaTime);
}

void CSwordHitboxObj::CollisionAttack(const FVector3D& HitPoint, CColliderBase* Dest)
{
    Dest->GetOwner()->Damage(mDamage, this);

    //Effect 추가 가능
    //CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

    //Effect->SetAnimation("Explosion");

    //Effect->SetWorldPos(HitPoint);
    //Effect->SetWorldScale(20.f, 20.f);

    Destroy();
}
