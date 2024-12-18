#pragma once
#include "GameInfo.h"

class CGameManager
{
private:
	CGameManager();
	~CGameManager();
	static CGameManager* mInst;
public:
	static CGameManager* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CGameManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
public:
	bool Init();
	void Run();
	EMainMenu Menu();
};

