#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"

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
    CStaticMeshComponent* Root = CreateComponent<CStaticMeshComponent>();

    Root->SetMesh("CenterRect");
    Root->SetShader("ColorMeshShader");

    Root->SetWorldPos(0.f, 0.f, 0.5f);

    SetRootComponent(Root);

    //Å° ÁöÁ¤
    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');
    mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');

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
	return true;
}
#pragma region movement
void CPlayerObject::MoveUp(float DeltaTime)
{
    FVector3D Pos = mRootComponent->GetWorldPosition();
    FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir * DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    FVector3D Pos = mRootComponent->GetWorldPosition();
    FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir* -1 * DeltaTime);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
}
#pragma endregion movement
