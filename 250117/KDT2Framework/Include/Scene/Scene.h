#pragma once

#include "../GameInfo.h"

class CScene abstract
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

protected:
	class CInput* mInput = nullptr;
	class CCameraManager* mCameraManager = nullptr;
	class CSceneCollision* mCollision = nullptr;
	std::list<CSharedPtr<class CSceneObject>>	mObjList;

public:
	class CInput* GetInput()	const
	{
		return mInput;
	}

	class CCameraManager* GetCameraManager()	const
	{
		return mCameraManager;
	}

	class CSceneCollision* GetCollision()	const
	{
		return mCollision;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void Input(float DeltaTime);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

public:
	template <typename T>
	T* CreateObj(const std::string& Name)
	{
		T* Obj = new T;

		Obj->mScene = this;
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		mObjList.push_back(Obj);

		return Obj;
	}

	template <typename T>
	void FindObjectsFromType(
		std::list<CSharedPtr<T>>& result)
	{
		auto	iter = mObjList.begin();
		auto	iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			T* Obj = dynamic_cast<T*>((*iter).Get());

			if (Obj)
				result.push_back(Obj);
		}
	}
};

