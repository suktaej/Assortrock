#pragma once
#include "GameInfo.h"
#include "BattleManager.h"
#include "Inventory.h"

enum class EMainMenu
{
	None,
	Battle,
	Store,
	Inventory,
	Exit
};

class CStoreManager;
// 전방선언: 어딘가에 지정한 타이의 클래스가 있다고 약속
// 포인터변수를 선언할 수 있도록 해주는 기능
//현재 CstoreManger에 대해 include되어있지 않음
//포인터 변수는 객체를 선언한 것이 아니라 메모리 주소를 가지고 있는 것일 뿐
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

private:
	CBattleManager* mBattleMgr = nullptr;
	CStoreManager* mStoreMgr = nullptr;
	CInventory* mInventory = nullptr;
private:
	EMainMenu Menu();
public:
	bool Init();
	void Run();
	CInventory* GetInventory() { return mInventory; }
};

