#pragma once
#include "GameInfo.h"

class CInventory
{
	friend class CGameManager;
private:
	CInventory();
	~CInventory();
	static CInventory* mInst;
public:
	static CInventory* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CInventory;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}

private:
	class CItem* mItem[MAX_ITEM] = {};
	int mItemCount = 0;
public:
	int InventoryCounter() { return mItemCount; }
	void AddInventoryCounter() { ++mItemCount; }
	void StackItem(EItemType,int);
	bool Init();
	void Run();
};

