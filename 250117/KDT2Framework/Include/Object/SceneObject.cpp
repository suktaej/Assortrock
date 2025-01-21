#include "SceneObject.h"
#include "../Component/SceneComponent.h"

CSceneObject::CSceneObject()
{
}

CSceneObject::CSceneObject(const CSceneObject& Obj)
{
}

CSceneObject::CSceneObject(CSceneObject&& Obj)
{
}

CSceneObject::~CSceneObject()
{
}

void CSceneObject::SetRootComponent(CSceneComponent* Root)
{
	mRootComponent = Root;
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
	mRootComponent->PreUpdate(DeltaTime);
}

void CSceneObject::Update(float DeltaTime)
{
	mRootComponent->Update(DeltaTime);
}

void CSceneObject::PostUpdate(float DeltaTime)
{
	mRootComponent->PostUpdate(DeltaTime);
}

void CSceneObject::Collision(float DeltaTime)
{
	mRootComponent->Collision(DeltaTime);
}

void CSceneObject::PreRender()
{
	mRootComponent->PreRender();
}

void CSceneObject::Render()
{
	mRootComponent->Render();
}

void CSceneObject::PostRender()
{
	mRootComponent->PostRender();
}

CSceneObject* CSceneObject::Clone()
{
	return nullptr;
}
