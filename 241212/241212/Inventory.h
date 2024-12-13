#pragma once
#include "GameInfo.h"

class CInventory
{
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
	class CItem* mItem[MAX_ITEM] = {};		//���漱��
	int mItemCount = 0;
public:
	int InventoryCounter() { return mItemCount; }
	//void AddInventoryCounter() { ++mItemCount; }
	//void StackItem(EItemType,int);
	bool IsFull() { return mItemCount == MAX_ITEM; }	//�߰�
	void AddItem(CItem*);
	void DeleteItem(int Index);
	CItem* GetItem(int Index);
	bool Init();
	void Run();
	void EquipFunction(class CPlayer*,int);
	void ItemSell(class CPlayer*,int);
};

