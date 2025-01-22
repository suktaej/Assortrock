#include "StaticMeshComponent.h"
#include "../Asset/Mesh/StaticMesh.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"

CStaticMeshComponent::CStaticMeshComponent()
{
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& Com) :
    CMeshComponent(Com)
{
}

CStaticMeshComponent::CStaticMeshComponent(CStaticMeshComponent&& Com) :
    CMeshComponent(Com)
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

void CStaticMeshComponent::SetShader(const std::string& Name)
{
    m_Shader = CShaderManager::GetInst()->FindShader(Name);
}

void CStaticMeshComponent::SetShader(CShader* Shader)
{
    m_Shader = Shader;
}

void CStaticMeshComponent::SetMesh(const std::string& Name)
{
    m_Mesh = (CStaticMesh*)CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);
}

void CStaticMeshComponent::SetMesh(CMesh* Mesh)
{
    m_Mesh = (CStaticMesh*)Mesh;
}

bool CStaticMeshComponent::Init()
{
    CMeshComponent::Init();

    return true;
}

bool CStaticMeshComponent::Init(const char* FileName)
{
    CMeshComponent::Init(FileName);

    return true;
}

void CStaticMeshComponent::PreUpdate(float DeltaTime)
{
    CMeshComponent::PreUpdate(DeltaTime);
}

void CStaticMeshComponent::Update(float DeltaTime)
{
    CMeshComponent::Update(DeltaTime);
}

void CStaticMeshComponent::PostUpdate(float DeltaTime)
{
    CMeshComponent::PostUpdate(DeltaTime);
}

void CStaticMeshComponent::Collision(float DeltaTime)
{
    CMeshComponent::Collision(DeltaTime);
}

void CStaticMeshComponent::PreRender()
{
    CMeshComponent::PreRender();
}

void CStaticMeshComponent::Render()
{
    CMeshComponent::Render();

    // Static Mesh 출력
    // 실제 기능으로 작동하는 것은 object가 아닌 component
    m_Shader->SetShader();
    m_Mesh->Render();
}

void CStaticMeshComponent::PostRender()
{
    CMeshComponent::PostRender();
}

CStaticMeshComponent* CStaticMeshComponent::Clone()
{
    return new CStaticMeshComponent(*this);
}
