#pragma once
#include "GameInfo.h"

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();
	static CObjectManager* mInst;
public:
	static CObjectManager* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CObjectManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	std::list<class CObject*> mObjList;
	//생성 된 모든 오브젝트를 관리
public:
	template<typename T>
	T* CreateObj()
	{
		T* Obj = new T;
	
		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		mObjList.emplace_back(Obj);
		return Obj;
	}
	//템플릿 선언은 header에 작성
	//T는 반드시 Obejct를 상속받아야 함
	bool Init();
	void Output(char* OutputBuffer);
	void Update(float DeltaTime);
};

