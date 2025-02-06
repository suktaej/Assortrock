#pragma once

#include "SceneComponent.h"

class CColliderBase abstract :
	public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CColliderBase();
	CColliderBase(const CColliderBase& Com);
	CColliderBase(CColliderBase&& Com);
	virtual ~CColliderBase();

protected:
	EColliderType	mColliderType;
	EColliderShape	mColliderShape;
	FVector3D		mMin;
	FVector3D		mMax;
	FCollisionProfile* mProfile = nullptr;
	bool			mCollision = false;
	std::function<void(const FVector3D&, CColliderBase*)>	mCollisionBeginFunc;
	std::function<void(CColliderBase*)>	mCollisionEndFunc;

#ifdef _DEBUG
	class CTransformCBuffer* mTransformCBuffer = nullptr;
	class CColliderCBuffer* mCBuffer = nullptr;
	CSharedPtr<class CMesh> mMesh;
	CSharedPtr<class CShader> mShader;
	bool mEnableRotation = false;
#endif // _DEBUG

public:
	FCollisionProfile* GetProfile()	const { return mProfile; }
	EColliderShape GetColliderShape()	const { return mColliderShape; }
	EColliderType GetColliderType()	const { return mColliderType; }
	const FVector3D& GetMin() { return mMin; }
	const FVector3D& GetMax() { return mMax; }
	void SetCollisionProfile(const std::string& Name);
	void CallCollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest);
	void CallCollisionEnd(CColliderBase* Dest);

public:
	bool Init() override;
	bool Init(const char* FileName) override;
	void PreUpdate(float DeltaTime) override;
	void Update(float DeltaTime) override;
	void PostUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	CColliderBase* Clone() override;
	virtual bool Collision(FVector3D& HitPoint, CColliderBase* Dest) = 0;


public:
	template <typename T>
	void SetCollisionBeginFunc(T* Obj,
		void (T::* Func)(const FVector3D&, CColliderBase*))
	{
		mCollisionBeginFunc = std::bind(Func, Obj,
			std::placeholders::_1, std::placeholders::_2);
	}

	template <typename T>
	void SetCollisionEndFunc(T* Obj,
		void (T::* Func)(CColliderBase*))
	{
		mCollisionEndFunc = std::bind(Func, Obj,
			std::placeholders::_1);
	}
};

