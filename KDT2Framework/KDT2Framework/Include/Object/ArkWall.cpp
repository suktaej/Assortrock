#include "ArkWall.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/SpriteComponent.h"
#include "../Share/Log.h"
#include "../Object/ArkPlayer.h"

CArkWall::CArkWall()
{
}

CArkWall::CArkWall(const CArkWall& Obj) :
    CSceneObject(Obj)
{
}

CArkWall::CArkWall(CArkWall&& Obj) :
    CSceneObject(Obj)
{
}

CArkWall::~CArkWall()
{
}

bool CArkWall::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderOBB2D>();

    //mRoot->SetMesh("CenterTexRect");
    mRoot->SetTexture("Wall", TEXT("Texture/block_wall.png"));
    mRoot->SetPivot(0.5f, 0.5f);
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(32, 700, 1.f);

    SetRootComponent(mRoot);
    
    mRoot->AddChild(mBody);

    mBody->SetCollisionProfile("Wall");
    mBody->SetBoxSize(32, 500);
    mBody->SetCollisionBeginFunc<CArkWall>(this, &CArkWall::CollisionWall);
    mBody->SetCollisionEndFunc<CArkWall>(this, &CArkWall::CollisionWallEnd);


    return true;
}

void CArkWall::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CArkWall::CollisionWall( const FVector3D& HitPoint, CColliderBase* Dest)
{
    CArkPlayer* Player = dynamic_cast<CArkPlayer*>(Dest);

    if (!strcmp(Dest->GetOwner()->GetName(), "Player"))
    {
        //Player->SetMoveStop();
    }
}

void CArkWall::CollisionWallEnd( CColliderBase* Dest)
{
}


