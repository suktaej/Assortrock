#include "Store.h"
#include "Item.h"
#include "ObjectManager.h"
//#include "GameManager.h"
#include "Inventory.h"
#include "Player.h"		//추가

CStore::CStore()
{
}

CStore::~CStore()
{
}

bool CStore::Init(EStoreType Type)
{
	mType = Type;

	switch (Type) 
	{
	case EStoreType::Weapon:
		for (int i = 0;i < 3;i++) 
		{
		mItem[i] = CObjectManager::GetInst()->GetItem(EItemType::Weapon, i);
		}
		break;
	case EStoreType::Armor:
		for (int i = 0;i < 3;i++) 
		{
		mItem[i] = CObjectManager::GetInst()->GetItem(EItemType::Armor, i);
		}
		break;
	case EStoreType::Sell:
		for (int i = 0; i < CInventory::GetInst()->InventoryCounter(); i++)
		{
			mItem[i] = CInventory::GetInst()->GetItem(i);
		}
	}
	return true;
}

void CStore::Run()
{
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();				//추가
	while (true)
	{
		system("cls");

		if (mItem[0] == nullptr)
			std::cout << "보유 아이템 없음" << std::endl;
	
		int ItemCount = 0;
		for (ItemCount = 0; ItemCount < 3; ++ItemCount)
		{
			std::cout << ItemCount + 1 << ". ";
			mItem[ItemCount]->Output();
		}
		std::cout << ItemCount+1 <<". 뒤로가기" << std::endl;

		//int PlayerGold = CObjectManager::GetInst()->GetPlayer()->GetGold();
		int PlayerGold = Player->GetGold();
		std::cout << "현재 보유금:" << PlayerGold << std::endl;

		std::cout << "아이템 선택 : ";
		int	Input;
		std::cin >> Input;

		if (Input == 4)
			break;

		else if (Input < 1 || Input > 4)
			continue;

		int ItemIndex = Input - 1;	//입력값이 아닌 배열의 목차
		//int EmptyInventory = CGameManager::GetInst()->GetInventory()->InventoryCounter();

		if (mItem[ItemIndex]->GetBuy() > PlayerGold)
		{
			std::cout << "보유금이 부족합니다" << std::endl;
			system("pause");
			continue;
		}
		//else if (EmptyInventory == MAX_ITEM)
		else if (CInventory::GetInst()->IsFull())		//추가
		{
			std::cout << "인벤토리 공간이 부족합니다" << std::endl;
			system("pause");
			continue;
		}
		//CObjectManager::GetInst()->GetPlayer()->SetGold(-1 * mItem[ItemIndex]->GetBuy());
		//CGameManager::GetInst()->GetInventory()->StackItem(mItem[ItemIndex]->GetType(), ItemIndex);
		CItem* Item = mItem[ItemIndex]->Clone();		//추가
		Player->SetGold(-Item->GetBuy());				//추가
		CInventory::GetInst()->AddItem(Item);			//추가
		//CGameManager::GetInst()->GetInventory()->AddInventoryCounter();
	}
}
void CStore::SellRun()
{
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();				//추가
	while (true)
	{
		system("cls");

		int ItemCount = 0;
	
		if (CInventory::GetInst()->InventoryCounter() == 0)
			std::cout << "보유 아이템 없음" << std::endl;
		else {
			for (ItemCount = 0; ItemCount < CInventory::GetInst()->InventoryCounter(); ++ItemCount)
			{
				std::cout << ItemCount + 1 << ". ";
				mItem[ItemCount]->Output();
			}
		}
		std::cout << ItemCount+1 <<". 뒤로가기" << std::endl;
		std::cout << Player->GetGold() << std::endl;

		std::cout << "아이템 선택 : ";

		int	Input;
		std::cin >> Input;

		if (Input == ItemCount+1)
			break;

		else if (Input < 1 || Input > ItemCount+1)
			continue;

		int ItemIndex = Input - 1;	//입력값이 아닌 배열의 목차

//		CInventory::GetInst()->DeleteItem(ItemIndex);
		Player->SetGold(mItem[ItemIndex]->GetSell());				//추가
	}
}

