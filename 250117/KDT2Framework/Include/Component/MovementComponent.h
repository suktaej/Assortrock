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
	virtual ~CMovementComponent();

protected:
	CSharedPtr<class CSceneComponent>	mUpdateComponent;

protected:
	FVector3D		mVelocity;
	FVector3D		mMoveStep;
	float			mSpeed = 1.f;

public:
	const FVector3D& GetMoveStep()	const
	{
		return mMoveStep;
	}

	float GetMoveDistance()	const
	{
		return mMoveStep.Length();
	}

public:
	void SetUpdateComponent(class CSceneComponent* Target);
	void SetMoveSpeed(float Speed)
	{
		mSpeed = Speed;
	}

	void Move(const FVector3D& Dir)
	{
		mVelocity += Dir;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PostRender();
	virtual CMovementComponent* Clone();
};

