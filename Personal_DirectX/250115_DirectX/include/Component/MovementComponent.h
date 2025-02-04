#pragma once

#include "Component.h"

class CMovementComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CMovementComponent();
	CMovementComponent(const CMovementComponent& Com);
	CMovementComponent(CMovementComponent&& Com);
	~CMovementComponent() override;

protected:
	CSharedPtr<class CSceneComponent> mUpdateComponent;
	EAxis mMoveAxis = EAxis::None;

	FVector3D mVelocity;
	FVector3D mMoveStep;

	float mSpeed = 1.f;
	bool mVelocityInit = true;

public:
	//업데이트 컴포넌트 지정
	void SetUpdateComponent(class CSceneComponent* Target){ mUpdateComponent = Target; }

	const FVector3D& GetMoveStep()	const { return mMoveStep; }
	float GetMoveDistance()	const { return mMoveStep.Length(); }

	void SetMoveSpeed(float Speed) { mSpeed = Speed; }
	void AddMove(const FVector3D& Dir) { mVelocity += Dir; }
	void SetMove(const FVector3D& Dir) { mVelocity = Dir; }
	void SetVelocityInit(bool VelocityInit) { mVelocityInit = VelocityInit; }
	void SetMoveAxis(EAxis Axis) { mMoveAxis = Axis; }
public:
	 bool Init() override;
	 bool Init(const char* FileName) override;
	 void PreUpdate(float DeltaTime) override;
	 void Update(float DeltaTime) override;
	 void PostUpdate(float DeltaTime) override;
	 void PostRender() override;
	 CMovementComponent* Clone() override;
};

