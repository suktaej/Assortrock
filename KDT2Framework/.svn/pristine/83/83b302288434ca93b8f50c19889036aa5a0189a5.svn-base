#pragma once

#include "../Share/Object.h"

class CSceneObject :
    public CObject
{
    friend class CScene;

protected:
    CSceneObject();
    CSceneObject(const CSceneObject& Obj);
    CSceneObject(CSceneObject&& Obj);
    virtual ~CSceneObject();

protected:
	class CScene* mScene = nullptr;
	std::string		mName;
	CSharedPtr<class CSceneComponent>	mRootComponent;
	float			mLifeTime = 0.f;

public:
	class CSceneComponent* GetRootComponent()
	{
		return mRootComponent;
	}

	class CScene* GetScene()	const
	{
		return mScene;
	}

	const char* GetName()	const
	{
		// c_str() 함수는 string이 가지고 있는 문자열 포인터를 반환한다.
		return mName.c_str();
	}

	void SetName(const std::string& Name)
	{
		mName = Name;
	}

	void SetLifeTime(float Time)
	{
		mLifeTime = Time;
	}

	void SetRootComponent(class CSceneComponent* Root);

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
	virtual CSceneObject* Clone();

public:
	template <typename T>
	T* CreateComponent()
	{
		T* Component = new T;

		if (!Component->Init())
		{
			SAFE_DELETE(Component);
			return nullptr;
		}

		return Component;
	}
};

