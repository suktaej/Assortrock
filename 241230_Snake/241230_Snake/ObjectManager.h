#pragma once
#include "GameInfo.h"

class CObjectManager
{
	DECLARE_SINGLE(CObjectManager)
private:
	std::list<class CObject*>	mObjList;
	int mItemSize = 5;
public:
	bool Init();
	//void Update(float DeltaTime);
	void Output(char* Buffer);
	void Update(float);
	//void Output();
public:
	template <typename T>
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
};
