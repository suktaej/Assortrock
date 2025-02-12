#include "ArkWall.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderOBB2D.h"
#include "../Share/Log.h"

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
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderOBB2D>();

    mRoot->SetMesh("CenterTexRect");
    //mRoot->AddTexture(0, "Wall", TEXT("Texture/ball_blue.png"), 1);
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(xSize, ySize, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Wall");
    mBody->SetBoxSize(xSize, ySize);
    mBody->SetCollisionBeginFunc<CArkWall>(this, &CArkWall::CollisionWall);
    mBody->SetCollisionEndFunc<CArkWall>(this, &CArkWall::CollisionWallEnd);

    mRoot->AddChild(mBody);

    return true;
}

void CArkWall::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CArkWall::CollisionWall( const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("Collision");
}

void CArkWall::CollisionWallEnd( CColliderBase* Dest)
{
    CLog::PrintLog("CollisionEnd");
}


