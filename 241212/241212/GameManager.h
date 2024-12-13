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
// ���漱��: ��򰡿� ������ Ÿ���� Ŭ������ �ִٰ� ���
// �����ͺ����� ������ �� �ֵ��� ���ִ� ���
//���� CstoreManger�� ���� include�Ǿ����� ����
//������ ������ ��ü�� ������ ���� �ƴ϶� �޸� �ּҸ� ������ �ִ� ���� ��
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

