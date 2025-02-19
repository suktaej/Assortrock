#pragma once

#include "../Share/Object.h"
#include "../Object/SceneObject.h"
#include "UIInfo.h"

class CWidget abstract	:
	public CObject
{
	friend class CSceneUIManager;

protected:
	CWidget();
	virtual ~CWidget();

protected:
	class CScene* mScene = nullptr;
	CSharedPtr<CSceneObject>	mOwnerObject;
	CSharedPtr<class CShader>	mShader;
	std::string	mName;
	FVector2D	mPos;
	FVector2D	mSize;
	FVector2D	mPivot;
	float		mRotation = 0.f;

	int			mZOrder = 0;

public:
	void SetOwnerObject(class CSceneObject* Object)
	{
		mOwnerObject = Object;
	}

public:
	const FVector2D& GetPos()	const
	{
		return mPos;
	}

	const FVector2D& GetSize()	const
	{
		return mSize;
	}

	const FVector2D& GetPivot()	const
	{
		return mPivot;
	}

	float GetRotation()	const
	{
		return mRotation;
	}

	int GetZOrder()	const
	{
		return mZOrder;
	}

public:
	void SetPos(const FVector2D& Pos)
	{
		mPos = Pos;
	}

	void SetPos(float x, float y)
	{
		mPos.x = x;
		mPos.y = y;
	}

	void SetSize(const FVector2D& Size)
	{
		mSize = Size;
	}

	void SetSize(float x, float y)
	{
		mSize.x = x;
		mSize.y = y;
	}

	void SetPivot(const FVector2D& Pivot)
	{
		mPivot = Pivot;
	}

	void SetPivot(float x, float y)
	{
		mPivot.x = x;
		mPivot.y = y;
	}

	void SetRotation(float Rotation)
	{
		if (Rotation > 360.f)
		{
			// 정수 부분만 남긴다.
			int	Angle1 = (int)Rotation;
			float Angle2 = Rotation - Angle1;

			Angle1 %= 360;

			mRotation = Angle1 + Angle2;
		}

		else if (Rotation < 0.f)
		{
			Rotation *= -1.f;

			// 정수 부분만 남긴다.
			int	Angle1 = (int)Rotation;
			float Angle2 = Rotation - Angle1;

			Angle1 %= 360;

			mRotation = 360.f - (Angle1 + Angle2);
		}

		else
			mRotation = Rotation;

	}

	void SetZOrder(int ZOrder)
	{
		mZOrder = ZOrder;
	}

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
	virtual bool CollisionMouse(const FVector2D& MousePos);

};

