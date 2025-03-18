#include "BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderOBB2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "SpriteEffect.h"
#include "../Scene/Scene.h"

CBulletObject::CBulletObject()
{
}

CBulletObject::CBulletObject(const CBulletObject& Obj)  :
    CSceneObject(Obj)
{
}

CBulletObject::CBulletObject(CBulletObject&& Obj) :
    CSceneObject(Obj)
{
}

CBulletObject::~CBulletObject()
{
}

void CBulletObject::SetBulletCollisionProfile(
    const std::string& Name)
{
    mBody->SetCollisionProfile(Name);
}

bool CBulletObject::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderOBB2D>();

    mMovement = CreateComponent<CMovementComponent>();

    mRoot->SetTexture("Arrow", TEXT("Texture/Weapon/Arrow.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

    SetRootComponent(mRoot);
    mBody->SetBoxSize(13.f, 5.f);
    mBody->SetCollisionBeginFunc<CBulletObject>(this, &CBulletObject::CollisionBullet);

    mRoot->AddChild(mBody);

    mMovement->SetUpdateComponent(mRoot);

    mMovement->SetMoveAxis(EAxis::X);
    mMovement->SetMoveSpeed(500.f);

    return true;
}

void CBulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    /*FVector3D Pos = mRoot->GetWorldPosition();

    Pos += mRoot->GetAxis(EAxis::Y) * mSpeed * DeltaTime;

    mRoot->SetWorldPos(Pos);*/
}

void CBulletObject::CollisionBullet(const FVector3D& HitPoint,
    CColliderBase* Dest)
{
    //CLog::PrintLog("Collision");

    Dest->GetOwner()->Damage(1.f, this);

    CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

    Effect->SetAnimation("Explosion");

    Effect->SetWorldPos(HitPoint);
    Effect->SetWorldScale(20.f, 20.f);

    Destroy();
}
