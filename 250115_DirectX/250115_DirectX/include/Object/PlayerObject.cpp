#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"

CPlayerObject::CPlayerObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj) :
    CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj) :
    CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
    //CStaticMeshComponent* Root = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CStaticMeshComponent>();
    mSub = CreateComponent<CStaticMeshComponent>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    //mRoot 설정
    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldPos(0.f, 0.f, 5.5f);
    
    SetRootComponent(mRoot);

    mRoot->AddChild(mRotationPivot);    
    //mRotationPivot 설정
    mRotationPivot->AddChild(mSub);

    //mSub 설정
    mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");
    
    mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetRelativePos(-2.f, 0.f, 0.f);
       
    //키 지정
    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');
    mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');
    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "MoveUp",
        EInputType::Hold,
        this,
        &CPlayerObject::MoveUp);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "MoveDown",
        EInputType::Hold,
        this,
        &CPlayerObject::MoveDown);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "RotationZ",
        EInputType::Hold,
        this,
        &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "RotationZInv",
        EInputType::Hold,
        this,
        &CPlayerObject::RotationZInv);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Fire",
        EInputType::Down,
        this,
        &CPlayerObject::Fire);
	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Rot = mRotationPivot->GetRelativeRotation();
    Rot.z += DeltaTime * mPivotRotationSpeed;
    mRotationPivot->SetRelativeRotationZ(Rot.z);
}

#pragma region movement
void CPlayerObject::MoveUp(float DeltaTime)
{
    FVector3D Pos = mRootComponent->GetWorldPosition();
    FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir * 3.f*DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    FVector3D Pos = mRootComponent->GetWorldPosition();
    FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir* -1 * 3.f* DeltaTime);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    FVector3D Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    FVector3D Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
}
void CPlayerObject::Fire(float DeltaTime)
{
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);
}
#pragma endregion movement
