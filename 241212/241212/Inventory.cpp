#include "Inventory.h"
#include "Item.h"
#include "ObjectManager.h"

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

void CInventory::StackItem(EItemType Type,int Index)
{
	mItem[mItemCount] = CObjectManager::GetInst()->CopyItem(Type,Index);
}

bool CInventory::Init()
{
	return true;
}

void CInventory::Run()
{
	system("cls");
	for (int i = 0; i < mItemCount; ++i)
	{
		std::cout << i + 1 << ". ";
		mItem[i]->Output();
	}
	std::cout << "현재 보유 아이템 " << mItemCount << "개" << std::endl;
	system("pause");
	return;
}
