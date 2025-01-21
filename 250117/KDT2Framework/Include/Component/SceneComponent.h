#pragma once

#include "Component.h"

class CSceneComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSceneComponent();
	CSceneComponent(const CSceneComponent& Com);
	CSceneComponent(CSceneComponent&& Com);
	virtual ~CSceneComponent();

protected:
	CSceneComponent* mParent = nullptr;
	std::vector<CSharedPtr<CSceneComponent>>	mChildList;

public:
	void AddChild(CSceneComponent* Child);

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CSceneComponent* Clone();

protected:
	FVector3D	mRelativeScale = FVector3D(1.f, 1.f, 1.f);
	FVector3D	mRelativeRot;
	FVector3D	mRelativePos;

	FVector3D	mWorldScale = FVector3D(1.f, 1.f, 1.f);
	FVector3D	mWorldRot;
	FVector3D	mWorldPos;

	FVector3D	mAxis[EAxis::End] =
	{
		FVector3D(1.f, 0.f, 0.f),
		FVector3D(0.f, 1.f, 0.f),
		FVector3D(0.f, 0.f, 1.f)
	};

	FMatrix		mmatScale;
	FMatrix		mmatRot;
	FMatrix		mmatTranslate;
	FMatrix		mmatWorld;

public:
	const FVector3D& GetAxis(EAxis::Type Axis)
	{
		return mAxis[Axis];
	}

	const FVector3D& GetRelativeScale()	const
	{
		return mRelativeScale;
	}

	const FVector3D& GetRelativeRotation()	const
	{
		return mRelativeRot;
	}

	const FVector3D& GetRelativePosition()	const
	{
		return mRelativePos;
	}

	const FVector3D& GetWorldScale()	const
	{
		return mWorldScale;
	}

	const FVector3D& GetWorldRotation()	const
	{
		return mWorldRot;
	}

	const FVector3D& GetWorldPosition()	const
	{
		return mWorldPos;
	}

public:
	void SetRelativeScale(const FVector3D& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScale(const FVector2D& Scale);
	void SetRelativeScale(float x, float y);

	void SetRelativeRotation(const FVector3D& Rot);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotation(const FVector2D& Rot);
	void SetRelativeRotation(float x, float y);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativeRotationAxis(float Angle, const FVector3D& Axis);

	void SetRelativePos(const FVector3D& Pos);
	void SetRelativePos(float x, float y, float z);
	void SetRelativePos(const FVector2D& Pos);
	void SetRelativePos(float x, float y);

	void SetWorldScale(const FVector3D& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(const FVector2D& Scale);
	void SetWorldScale(float x, float y);

	void SetWorldRotation(const FVector3D& Rot);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(const FVector2D& Rot);
	void SetWorldRotation(float x, float y);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldRotationAxis(float Angle, const FVector3D& Axis);

	void SetWorldPos(const FVector3D& Pos);
	void SetWorldPos(float x, float y, float z);
	void SetWorldPos(const FVector2D& Pos);
	void SetWorldPos(float x, float y);
};

