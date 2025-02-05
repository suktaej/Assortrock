#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"

CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)   :
    CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj) :
    CSceneObject(Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

bool CMonsterObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderAABB2D>();
    //mBody = CreateComponent<CColliderSphere2D>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Monster");
    //mBody->SetRadius(50.f);
    mBody->SetBoxSize(100.f, 100.f);
    mBody->SetCollisionBeginFunc<CMonsterObject>(this,
        &CMonsterObject::CollisionMonster);

    mRoot->AddChild(mBody);

    return true;
}

void CMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    if (mTarget)
    {
        if (!mTarget->IsActive())
            mTarget = nullptr;
    }
}

float CMonsterObject::Damage(float Attack,
    CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CMonsterObject::CollisionMonster(
    const FVector3D& HitPoint, CColliderBase* Dest)
{
}
