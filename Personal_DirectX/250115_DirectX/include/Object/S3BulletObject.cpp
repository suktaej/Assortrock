#include "S3BulletObject.h"
#include "../Component/StaticMeshComponent.h"

CS3BulletObject::CS3BulletObject()
{
}

CS3BulletObject::CS3BulletObject(const CS3BulletObject& Obj) :
    CSceneObject(Obj)
{
}

CS3BulletObject::CS3BulletObject(CS3BulletObject&& Obj) :
    CSceneObject(Obj)
{
}

CS3BulletObject::~CS3BulletObject()
{
}

bool CS3BulletObject::Init()
{
    mRoot = CreateComponent<CSceneComponent>();
    mPivot = CreateComponent<CSceneComponent>();
    mMesh = CreateComponent<CStaticMeshComponent>();

    mMesh->SetMesh("CenterRect");
    mMesh->SetShader("ColorMeshShader");

    mMesh->SetWorldScale(0.5f, 0.5f, 1.f);
    mMesh ->SetRelativePos(-1.5f, 0.f);

    SetRootComponent(mRoot);

    mRoot->AddChild(mPivot);
    mPivot->AddChild(mMesh);

    return true;
}

void CS3BulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Pos = mRoot->GetWorldPosition();

    Pos += mRoot->GetAxis(EAxis::Y) * mSpeed * DeltaTime;

    mRoot->SetWorldPos(Pos);
    
    FVector3D Rot = mPivot->GetRelativeRotation();
    Rot.z += DeltaTime * 720.f;
    mPivot->SetRelativeRotationZ(Rot.z);
}

