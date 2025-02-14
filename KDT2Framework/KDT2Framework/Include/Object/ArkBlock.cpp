#include "ArkBlock.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/SpriteComponent.h"
#include "../Share/Log.h"

CArkBlock::CArkBlock()
{
}

CArkBlock::CArkBlock(const CArkBlock& Obj) :
    CSceneObject(Obj)
{
}

CArkBlock::CArkBlock(CArkBlock&& Obj) :
    CSceneObject(Obj)
{
}

CArkBlock::~CArkBlock()
{
}

bool CArkBlock::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderOBB2D>();

    //mRoot->SetMesh("CenterRect");
    mRoot->SetTexture("Block", TEXT("Texture/block_blue.png"));
    mRoot->SetPivot(0.5f, 0.5f);
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(64.f, 32.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Block");
    mBody->SetBoxSize(64.f, 32.f);
    mBody->SetCollisionBeginFunc<CArkBlock>(this, &CArkBlock::CollisionBall);
    mBody->SetCollisionEndFunc<CArkBlock>(this, &CArkBlock::CollisionBallEnd);

    mRoot->AddChild(mBody);

    return true;
}

void CArkBlock::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

float CArkBlock::Damage(float Attack,
    CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CArkBlock::CollisionBall( const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("Collision");
}

void CArkBlock::CollisionBallEnd( CColliderBase* Dest)
{
    CLog::PrintLog("CollisionEnd");
}

