#include "HitboxObj.h"

CHitboxObj::CHitboxObj()
{
}

CHitboxObj::CHitboxObj(const CHitboxObj& Obj)
{
}

CHitboxObj::CHitboxObj(CHitboxObj&& Obj)
{
}

CHitboxObj::~CHitboxObj()
{
}

bool CHitboxObj::Init()
{
    CSceneObject::Init();

    return true;
}

void CHitboxObj::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CHitboxObj::CollisionAttack(const FVector3D& HitPoint, CColliderBase* Dest)
{
}

void CHitboxObj::SetAttackCollisionProfile(const std::string& Name)
{
	mBody->SetCollisionProfile(Name);
}

void CHitboxObj::AttackAction(FVector3D Pos, FVector3D Dir, FVector3D Rot)
{
    mRoot->SetWorldPos(Pos + Dir * 20.f);
    mRoot->SetWorldRotation(Rot);
}
