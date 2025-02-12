#include "ArkBall.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Share/Log.h"
#include "cmath"

CArkBall::CArkBall()
{
}

CArkBall::CArkBall(const CArkBall& Obj) :
    CSceneObject(Obj)
{
}

CArkBall::CArkBall(CArkBall&& Obj) :
    CSceneObject(Obj)
{
}

CArkBall::~CArkBall()
{
}

void CArkBall::SetBallCollisionProfile(const std::string& Name)
{ 
    mBody->SetCollisionProfile(Name);
}

bool CArkBall::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderSphere2D>();
    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();

    mRoot->SetMesh("CenterTexRect");
    //mRoot->AddTexture(0, "Ball", TEXT("Texture/ball_blue.png"), 1);
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(14.f, 14.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Ball");
    mBody->SetRadius(7.f);
    mBody->SetCollisionBeginFunc<CArkBall>(this, &CArkBall::CollisionBall);
    mBody->SetCollisionEndFunc<CArkBall>(this, &CArkBall::CollisionBallEnd);

    mRoot->AddChild(mBody);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveAxis(EAxis::Y);
    mMovement->SetMoveSpeed(500.f);
    mRoot->SetWorldRotationZ(-45);

    return true;
}

void CArkBall::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CArkBall::CollisionBall( const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("Wall Collision");

    FVector3D BallAxis = mRoot->GetAxis(EAxis::Y);
	FVector3D NormalLine;


    if (!strcmp(Dest->GetOwner()->GetName(), "RWall"))
    {
        NormalLine.x = 1;
        ReflectionFunc(BallAxis, NormalLine);
    }
    else if (!strcmp(Dest->GetOwner()->GetName(), "LWall"))
    {
        NormalLine.x = -1;
        ReflectionFunc(BallAxis, NormalLine);
    }
    else if (!strcmp(Dest->GetOwner()->GetName(), "TWall"))
    {
        NormalLine.y = -1;
        ReflectionFunc(BallAxis, NormalLine);
    }
    else if (!strcmp(Dest->GetOwner()->GetName(), "Player"))
    {
        NormalLine.y = 1;
        ReflectionFunc(BallAxis, NormalLine);
    }
    else if (!strcmp(Dest->GetOwner()->GetName(), "Pit"))
    {
        Destroy();
    }
    else if (!strcmp(Dest->GetOwner()->GetName(), "Block"))
    {
        Dest->GetOwner()->Damage(1.f,this);
    }
}

void CArkBall::CollisionBallEnd( CColliderBase* Dest)
{
    CLog::PrintLog("CollisionEnd");
}

void CArkBall::ReflectionFunc(const FVector3D& BallAxis, const FVector3D& NormalLine) 
{
    FVector3D Reflection;
    float AngleRad = 0;
    float RefAngle = 0;

    float DotProduct = BallAxis.Dot(NormalLine);
    Reflection = BallAxis - (NormalLine * 2.f * DotProduct);
    AngleRad = atan2(Reflection.y, Reflection.x);
    RefAngle = DirectX::XMConvertToDegrees(AngleRad);
    mRoot->SetRelativeRotationZ(RefAngle - 90);
}

