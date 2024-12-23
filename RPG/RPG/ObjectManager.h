#pragma once
#include "GameInfo.h"
#define OBJECT_SIZE 10

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();
	static CObjectManager* mInst;
public:
	static CObjectManager* GetInst()
	{
		if (nullptr == mInst)
			mInst = new CObjectManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	class CObject* mObjectList[OBJECT_SIZE];
	class CPlayer* mPlayer = nullptr;
	int mObjectCount = 0;
public:
	class CObject* GetObject(int Index) { return mObjectList[Index]; }
public:
	bool Init();
	void Output();

	void CreateMonsterLsit();
	void CreateItemList();
};

