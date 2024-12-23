#pragma once
#include "GameInfo.h"

enum class EMainMenu:unsigned char
{
	None,
	Battle,
	Store,
	Inventory,
	Exit
};

class CGameManager
{
private:
	CGameManager();
	~CGameManager();
	static CGameManager* mInst;
public:
	static CGameManager* GetInst()
	{
		if (nullptr == mInst)
			mInst = new CGameManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	EMainMenu Menu();
public:
	bool Init();
	void Run();
};

