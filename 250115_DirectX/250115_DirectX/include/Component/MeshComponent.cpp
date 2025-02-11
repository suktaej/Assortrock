#include "MeshComponent.h"
#include "../Shader/TransformCBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"

CMeshComponent::CMeshComponent()
{
    m_TransformCBuffer = new CTransformCBuffer;
    m_TransformCBuffer->Init();
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com)   :
    CSceneComponent(Com)
{
    m_TransformCBuffer = Com.m_TransformCBuffer->Clone();
}

CMeshComponent::CMeshComponent(CMeshComponent&& Com) :
    CSceneComponent(Com)
{
    m_TransformCBuffer = Com.m_TransformCBuffer;
    Com.m_TransformCBuffer = nullptr;
}

CMeshComponent::~CMeshComponent()
{
    SAFE_DELETE(m_TransformCBuffer);
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

    m_TransformCBuffer->SetWorldMatrix(m_MatWorld);
    //������� ����
    //�̴� �θ��� ������Ʈ(scene component)���� 
    //���� ��������� �����Ͽ� ������ ���� �� �ֵ���

    //�ӽð�ü
    //FMatrix matProj = DirectX::XMMatrixPerspectiveFovLH( DirectX::XMConvertToRadians(90.f), 1280.f / 720.f, 0.5f, 1000.f);
    //m_TransformCBuffer->SetProjMatrix(matProj);

    //ī�޶� �޴��� ����
    FMatrix matView = mScene->GetCameraManager()->GetViewMatrix();
    FMatrix matProj = mScene->GetCameraManager()->GetProjMatrix();

    m_TransformCBuffer->SetViewMatrix(matView);
    m_TransformCBuffer->SetProjMatrix(matProj);

    m_TransformCBuffer->UpdateBuffer();
}

void CMeshComponent::PostRender()
{
    CSceneComponent::PostRender();
}

CMeshComponent* CMeshComponent::Clone()
{
    return nullptr;
}
