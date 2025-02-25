#include "MeshComponent.h"
#include "../Shader/TransformCBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "../Asset/Material/Material.h"

CMeshComponent::CMeshComponent()
{
    mRenderType = EComponentRender::Render;
    mRenderLayerName = "Object";
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com)   :
    CSceneComponent(Com)
{
}

CMeshComponent::CMeshComponent(CMeshComponent&& Com) :
    CSceneComponent(Com)
{
}

CMeshComponent::~CMeshComponent()
{
}

bool CMeshComponent::Init()
{
    CSceneComponent::Init();

    return true;
}

bool CMeshComponent::Init(const char* FileName)
{
    CSceneComponent::Init(FileName);

    return true;
}

void CMeshComponent::PreUpdate(float DeltaTime)
{
    CSceneComponent::PreUpdate(DeltaTime);
}

void CMeshComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CMeshComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CMeshComponent::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CMeshComponent::PreRender()
{
    CSceneComponent::PreRender();
}

void CMeshComponent::Render()
{
    CSceneComponent::Render();

    mTransformCBuffer->SetWorldMatrix(mmatWorld);

    FMatrix matView, matProj;
    matView = mScene->GetCameraManager()->GetViewMatrix();
    matProj = mScene->GetCameraManager()->GetProjMatrix();

    mTransformCBuffer->SetViewMatrix(matView);
    mTransformCBuffer->SetProjMatrix(matProj);

    /*FMatrix matProj = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XMConvertToRadians(90.f),
        1280.f / 720.f, 0.5f, 1000.f);

    mTransformCBuffer->SetProjMatrix(matProj);*/

    mTransformCBuffer->UpdateBuffer();
}

void CMeshComponent::PostRender()
{
    CSceneComponent::PostRender();
}

CMeshComponent* CMeshComponent::Clone()
{
    return nullptr;
}
