#include "StaticMeshComponent.h"
#include "../Shader/TrnasformBuffer.h"

CStaticMeshComponent::CStaticMeshComponent()
{
	//m_TransfromCBuffer = new CTransformCBuffer;
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& Com)
{
	//m_TransfromCBuffer = Com.m_TransfromC;
}

CStaticMeshComponent::CStaticMeshComponent(CStaticMeshComponent&& Com)
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

bool CStaticMeshComponent::Init()
{
	return false;
}

bool CStaticMeshComponent::Init(const char* FileName)
{
	return false;
}

void CStaticMeshComponent::PreUpdate(float DeltaTime)
{
}

void CStaticMeshComponent::Update(float DeltaTime)
{
}

void CStaticMeshComponent::PostUpdate(float DeltaTime)
{
}

void CStaticMeshComponent::PreRender()
{
}

void CStaticMeshComponent::Render()
{
}

void CStaticMeshComponent::PostRender()
{
}

void CStaticMeshComponent::Collision(float DeltaTime)
{
}

CSceneComponent* CStaticMeshComponent::Clone()
{
	return nullptr;
}
