#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

enum class EInventoryMenu
{
	None,
	Equip,
	Sell,
	Back
};

CInventory* CInventory::mInst = nullptr;

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
	for (int i = 0;i < mItemCount;i++)
		SAFE_DELETE(mItem[i]);
}

//void CInventory::StackItem(EItemType Type,int Index)
//{
//	mItem[mItemCount] = CObjectManager::GetInst()->CopyItem(Type,Index);
//}

void CInventory::AddItem(CItem* NewItem)		//�߰�
{
	mItem[mItemCount] = NewItem;
	++mItemCount;
}

//void CInventory::DeleteItem(int Index)
//{
//	mItem[Index] = mItem[mItemCount];
//	--mItemCount;
//}

CItem* CInventory::GetItem(int Index)
{
	return mItem[Index];
}
void CInventory::EquipFunction(CPlayer* Player, int Index)
{
	CItem* EquipItem = Player->Equip(mItem[Index]);

	if (nullptr == EquipItem)
	{
		mItem[Index] = mItem[mItemCount - 1];
		mItem[mItemCount - 1] = nullptr;
		--mItemCount;
	}

	else
	{
		mItem[Index] = EquipItem;
	}
}

void CInventory::ItemSell(CPlayer* Player, int Index)
{
	Player->SetGold(mItem[Index]->GetSell());
	CItem* DeleteItem = mItem[Index];

	if (mItemCount >= 2)
	{
		mItem[Index] = mItem[mItemCount - 1];
		mItem[mItemCount - 1] = nullptr;
	}
	else
		mItem[Index] = nullptr;
	--mItemCount;
	delete DeleteItem;
}

bool CInventory::Init() { return true; }

void CInventory::Run()
{
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();
	
	while (true) {
		system("cls");
		for (int i = 0; i < mItemCount; ++i)
		{
			std::cout << i + 1 << ". ";
			mItem[i]->Output();
		}
		std::cout << mItemCount + 1 << ". 뒤로가기" << std::endl;
		
		std::cout << "장착무기:";
		CItem* Equip = Player->GetEquipItem(EEquip::Weapon);
		if (Equip)
			std::cout << Equip->GetName();
		else
			std::cout << "없음";
		
		std::cout << "\t장착방어구:";
		Equip = Player->GetEquipItem(EEquip::Armor);

		if (Equip)
			std::cout << Equip->GetName();
		else
			std::cout << "없음";

		std::cout << std::endl;
		std::cout << "아이템 선택 : ";
		int	Input;
		std::cin >> Input;

		if (Input == mItemCount + 1)
			return;

		else if (Input < 1 || Input > mItemCount + 1)
			continue;

		std::cout << "1.장착" << std::endl;
		std::cout << "2.판매" << std::endl;
		std::cout << "3.다시 선택" << std::endl;
		int InvMenu = 0;
		std::cin >> InvMenu;
		
		int	Index = Input - 1;

		if (InvMenu >= static_cast<int>(EInventoryMenu::Back)||
			InvMenu <= static_cast<int>(EInventoryMenu::None))
			continue;

		switch (InvMenu)
		{
		case static_cast<int>(EInventoryMenu::Equip):
			EquipFunction(Player, Index);
			break;
		case static_cast<int>(EInventoryMenu::Sell):
			ItemSell(Player, Index);
			break;
		}
	}
}

