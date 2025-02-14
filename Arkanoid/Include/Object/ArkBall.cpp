#include "ArkBall.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
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
    mRoot->SetWorldRotationZ(45);

    return true;
}

void CArkBall::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CArkBall::CollisionBall( const FVector3D& HitPoint, CColliderBase* Dest)
{
    FVector3D BallAxis = mRoot->GetAxis(EAxis::Y);
	FVector2D NormalLine;
    CColliderOBB2D* OBB;

    if (OBB = dynamic_cast<CColliderOBB2D*>(Dest))
    {
        FVector2D LocalCenter(HitPoint.x - OBB->GetBox().Center.x, HitPoint.y - OBB->GetBox().Center.y);
        //충돌점을 OBB의 로컬 좌표로 이동

        float CenterProjX = LocalCenter.Dot(OBB->GetBox().Axis[EAxis::X]);
        float CenterProjY = LocalCenter.Dot(OBB->GetBox().Axis[EAxis::Y]);
        //충돌점을 OBB의 양 축에 투영

        if (fabs(CenterProjX) >= OBB->GetBox().HalfSize.x-1.f)
            NormalLine = OBB->GetBox().Axis[EAxis::X] * (CenterProjX >= 0 ? 1.f : -1.f);
        else if (fabs(CenterProjY) >= OBB->GetBox().HalfSize.y-1.f)
            NormalLine = OBB->GetBox().Axis[EAxis::Y] * (CenterProjY >= 0 ? 1.f : -1.f);

		FVector3D NormalLine3D(NormalLine.x,NormalLine.y,0);
        ReflectionFunc(BallAxis, NormalLine3D);
    }
 
    /*if (!strcmp(Dest->GetOwner()->GetName(), "RWall"))
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
    else */
    if (!strcmp(Dest->GetOwner()->GetName(), "Pit"))
    {
        Destroy();
    }
    //else if (!strcmp(Dest->GetOwner()->GetName(), "Block"))
    //{
    //    //HitPoint의 위치와 min,max를 비교하여 상하좌우를 판단 -> 함수?
    //    //일치하는 방향의 법선벡터를 설정하
    //    Dest->GetOwner()->Damage(1.f,this);
    //}
}

void CArkBall::CollisionBallEnd( CColliderBase* Dest)
{
    CLog::PrintLog("CollisionEnd");
}

void CArkBall::ReflectionFunc(const FVector3D& BallAxis, const FVector3D& NormalLine) 
{
    FVector3D Reflection;   //반사벡터
    float AngleRad = 0;     //반사벡터의 radian
    float RefAngle = 0;     //반사벡터의 degree

    float DotProduct = BallAxis.Dot(NormalLine);    //입사각과 법선의 내적
    Reflection = BallAxis - (NormalLine * 2.f * DotProduct);    //반사벡터 공식
    AngleRad = atan2(Reflection.y, Reflection.x);       //벡터의 라디안화
    RefAngle = DirectX::XMConvertToDegrees(AngleRad);   //라디안의 각도화
    mRoot->SetRelativeRotationZ(RefAngle - 90);         //Y축 기준으로 각도가 정해졌으므로 -90
}

FVector2D& CArkBall::NormalLineCal(const FVector3D& HitPoint, CColliderBase* Dest)
{
    FVector2D NormalLine;
    CColliderOBB2D* OBB;

    OBB = dynamic_cast<CColliderOBB2D*>(Dest);

	FVector2D LocalCenter(HitPoint.x - OBB->GetBox().Center.x, HitPoint.y - OBB->GetBox().Center.y);
	//충돌점을 OBB의 로컬 좌표로 이동

	float CenterProjX= LocalCenter.Dot(OBB->GetBox().Axis[EAxis::X]);
	float CenterProjY= LocalCenter.Dot(OBB->GetBox().Axis[EAxis::Y]);
	//충돌점을 OBB의 양 축에 투영
	
    if (fabs(CenterProjX) >= OBB->GetBox().HalfSize.x)
        NormalLine = OBB->GetBox().Axis[EAxis::X] * (CenterProjX > 0 ? 1.f : -1.f);
    else if (fabs(CenterProjY) >= OBB->GetBox().HalfSize.y)
        NormalLine = OBB->GetBox().Axis[EAxis::Y] * (CenterProjY > 0 ? 1.f : -1.f);
    
    return NormalLine;
}

