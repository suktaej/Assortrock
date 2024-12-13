#pragma once
#include "GameInfo.h"
#include "Player.h"
#include "GameAI.h"

class CGameManager
{
private:
	CGameManager();
	~CGameManager();
private:
	static CGameManager* mInst;
	CPlayer* mPlayer = nullptr;
	CAI* mAI = nullptr;
public:
	bool Init();
	void Run();
public:
	static CGameManager* GetInst()
	{
		if (nullptr == mInst)
			mInst = new CGameManager;
		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst != nullptr)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};

//CGameManager* CGameManager::mInst = nullptr;
//전역으로 선언하지 않고 cpp에서 선언
