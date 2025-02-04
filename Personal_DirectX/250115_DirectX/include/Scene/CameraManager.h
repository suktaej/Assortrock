#pragma once

#include "../GameInfo.h"
#include "../Component/CameraComponent.h"

class CCameraManager
{
	friend class CScene;
private:
	CCameraManager();
	~CCameraManager();
private:
	//카메라 컴포넌트
	CSharedPtr<CCameraComponent> m_ViewTarget;
public:
	CCameraComponent* GetViewTarget() const { return m_ViewTarget; }
	const FMatrix& GetViewMatrix() const { return m_ViewTarget->GetViewMatrix(); }
	const FMatrix& GetProjMatrix() const { return m_ViewTarget->GetProjMatrix(); }
public:
	void SetViewTarget(CCameraComponent* ViewTarget);
public:
	bool Init();
	void Update(float DeltaTime);
};

