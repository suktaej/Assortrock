#pragma once
#include "GameInfo.h"
#include "Player.h"
#include "Monster.h"
#include "Inventory.h"

class CItem;			//穿号識情
class CObjectManager	//穿号識情
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
	CPlayer* mPlayer = nullptr;
	CMonster* mMonster[static_cast<int>(EBattleType::End)] = {};
	class CItem* mItem[static_cast<int>(EItemType::End)][3];	
	int ItemSize = 0;
	//穿号識情
private:
	bool LoadMonster();
	bool LoadItem();
public:
	CPlayer* GetPlayer() { return mPlayer; }
	bool Init();
	CMonster* CreateMonster(EBattleType);
	CItem* GetItem(EItemType Type, int Index);
	CItem* CopyItem(EItemType Type, int Index);
	int GetItemSize() { return ItemSize; }
};

