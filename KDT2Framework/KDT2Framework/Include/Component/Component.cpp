#include "Component.h"

CComponent::CComponent()
{
}

CComponent::CComponent(const CComponent& Com)
{
}

CComponent::CComponent(CComponent&& Com)
{
}

CComponent::~CComponent()
{
}

bool CComponent::Init()
{
    return true;
}

bool CComponent::Init(const char* FileName)
{
    return true;
}

void CComponent::PreUpdate(float DeltaTime)
{
}

void CComponent::Update(float DeltaTime)
{
}

void CComponent::PostUpdate(float DeltaTime)
{
}

void CComponent::Collision(float DeltaTime)
{
}

void CComponent::PreRender()
{
}

void CComponent::Render()
{
}

void CComponent::PostRender()
{
}

CComponent* CComponent::Clone()
{
    return nullptr;
}

void CComponent::EraseOwner()
{
}
