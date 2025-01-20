#include "MeshComponent.h"

CMeshComponent::CMeshComponent()
{
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com)
{
}

CMeshComponent::CMeshComponent(CMeshComponent&& Com)
{
}

CMeshComponent::~CMeshComponent()
{
}

bool CMeshComponent::Init()
{
    return false;
}

bool CMeshComponent::Init(const char* FileName)
{
    return false;
}

void CMeshComponent::PreUpdate(float DeltaTime)
{
}

void CMeshComponent::Update(float DeltaTime)
{
}

void CMeshComponent::PostUpdate(float DeltaTime)
{
}

void CMeshComponent::PreRender()
{
}

void CMeshComponent::Render()
{
}

void CMeshComponent::PostRender()
{
}

void CMeshComponent::Collision(float DeltaTime)
{
}

CSceneComponent* CMeshComponent::Clone()
{
    return nullptr;
}
