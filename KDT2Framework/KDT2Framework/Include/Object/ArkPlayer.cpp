#include "ArkPlayer.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "ArkBall.h"

CArkPlayer::CArkPlayer()
{
}

CArkPlayer::CArkPlayer(const CArkPlayer& Obj) :
    CSceneObject(Obj)
{
}

CArkPlayer::CArkPlayer(CArkPlayer&& Obj) :
    CSceneObject(Obj)
{
}

CArkPlayer::~CArkPlayer()
{
}

bool CArkPlayer::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    //mSub = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderAABB2D>();
    //mLine = CreateComponent<CColliderLine2D>();
    mCamera = CreateComponent<CCameraComponent>();

    mMovement = CreateComponent<CMovementComponent>();
    //mRotation = CreateComponent<CRotationComponent>();

    mRoot->SetMesh("CenterTexRect");
    //mRoot->AddTexture(0, "Bar", TEXT("Texture/block_bar.png"), 0);
    //mRoot->SetOpacity(0, 0.5f);
    //mRoot->SetBaseColor(0, 1.f, 0.f, 0.f, 1.f);
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldPos(0.f, -300.f, 0.f);
    mRoot->SetWorldScale(76.f, 8.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(76.f, 8.f);
    //mBody->SetRadius(50.f);

    mRoot->AddChild(mBody);
    //mRoot->AddChild(mSub);

    //mSub->SetMesh("CenterTexRect");
    //mSub->SetShader("ColorMeshShader");
    //mSub->SetRelativePos(0.f, 30.f, 0.f);
    //mSub->SetWorldScale(16.f, 16.f);

    //mRoot->AddChild(mLine);

    //mLine->SetCollisionProfile("Player");
    //mLine->SetRelativePos(0.f, 50.f);
    //mLine->SetLineDistance(300.f);

    mCamera->SetProjectionType(ECameraProjectionType::Ortho);

    //mRoot->AddChild(mCamera);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(400.f);

    //mRotation->SetUpdateComponent(mRotationPivot);
    //mRotation->SetVelocityInit(false);
    //mRotation->SetMoveZ(360.f);

    mScene->GetInput()->AddBindKey("MoveLeft", 'A');
    mScene->GetInput()->AddBindKey("MoveRight", 'D');

    mScene->GetInput()->AddBindFunction<CArkPlayer>("MoveLeft", EInputType::Hold, this, &CArkPlayer::MoveLeft);
    mScene->GetInput()->AddBindFunction<CArkPlayer>("MoveRight", EInputType::Hold, this, &CArkPlayer::MoveRight);

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);

    mScene->GetInput()->AddBindFunction<CArkPlayer>("Fire", EInputType::Down, this, &CArkPlayer::Fire);

    return true;
}

void CArkPlayer::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CArkPlayer::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);
}
void CArkPlayer::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));
}

//void CArkPlayer::MoveUp(float DeltaTime)
//{
//    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));
//}
//
//void CArkPlayer::MoveDown(float DeltaTime)
//{
//    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);
//}
//
//void CArkPlayer::RotationZ(float DeltaTime)
//{
//    FVector3D   Rot = mRootComponent->GetWorldRotation();
//    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
//}
//
//void CArkPlayer::RotationZInv(float DeltaTime)
//{
//    FVector3D   Rot = mRootComponent->GetWorldRotation();
//    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
//}

void CArkPlayer::Fire(float DeltaTime)
{
	CArkBall* Ball = mScene->CreateObj<CArkBall>("Ball");

	Ball->SetBallCollisionProfile("Ball");

	CSceneComponent* Root = Ball->GetRootComponent();

	FVector3D Pos = mRoot->GetWorldPosition();
	FVector3D Dir = mRoot->GetAxis(EAxis::Y);

	Root->SetWorldScale(14.f, 14.f);
	//Root->SetWorldRotation(mRoot->GetWorldRotation());
	Root->SetWorldPos(Pos + Dir * 30.f);
}

