#include "CameraManager.h"
#include "../Component/CameraComponent.h"

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

const FVector3D& CCameraManager::GetCameraWorldPos() const
{
	return mViewTarget->GetWorldPosition();
}

const FMatrix& CCameraManager::GetViewMatrix() const
{
	return mViewTarget->GetViewMatrix();
}

const FMatrix& CCameraManager::GetProjMatrix() const
{
	return mViewTarget->GetProjMatrix();
}

void CCameraManager::SetViewTarget(CCameraComponent* ViewTarget)
{
	mViewTarget = ViewTarget;
}

bool CCameraManager::Init()
{
	return true;
}

void CCameraManager::Update(float DeltaTime)
{
	if (mViewTarget)
	{
		if (!mViewTarget->IsActive())
			mViewTarget = nullptr;
	}
}
