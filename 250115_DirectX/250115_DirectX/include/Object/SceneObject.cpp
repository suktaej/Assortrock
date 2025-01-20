#include "SceneObject.h"
#include "../Component/SceneComponent.h"

CSceneObject::CSceneObject()
{
}
CSceneObject::~CSceneObject()
{
}
//트랜스폼을 공유하기 위함
void CSceneObject::SetRootComponent(CSceneComponent* Root)
{
	m_RootComponent = Root;
}

bool CSceneObject::Init()
{
	return true;
}

bool CSceneObject::Init(const char* FileName)
{
	return true;
}

void CSceneObject::PreUpdate(float DeltaTime)
{
}

void CSceneObject::Update(float DeltaTime)
{
}

void CSceneObject::PostUpdate(float DeltaTime)
{
}

void CSceneObject::PreRender()
{
}

void CSceneObject::Render()
{
}

void CSceneObject::PostRender()
{
}

void CSceneObject::Collision(float DeltaTime)
{
}

CSceneObject* CSceneObject::Clone()
{
	return nullptr;
}
