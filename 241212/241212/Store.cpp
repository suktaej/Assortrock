#include "Store.h"
#include "Item.h"
#include "ObjectManager.h"
#include "GameManager.h"

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
	}
	return true;
}

void CStore::Run()
{
	while (true)
	{
		system("cls");

		for (int i = 0; i < 3; ++i)
		{
			std::cout << i + 1 << ". ";
			mItem[i]->Output();
		}
		std::cout << "4. 뒤로가기" << std::endl;
		
		int PlayerGold = CObjectManager::GetInst()->GetPlayer()->GetGold();
		std::cout << "현재 보유금:" << PlayerGold << std::endl;

		std::cout << "아이템 선택 : ";
		int	Input;
		std::cin >> Input;

		if (Input == 4)
			break;

		else if (Input < 1 || Input > 4)
			continue;

		int ItemIndex = Input - 1;
		int EmptyInventory = CGameManager::GetInst()->GetInventory()->InventoryCounter();

		if(mItem[ItemIndex]->GetBuy() > PlayerGold)
		{
			std::cout << "보유금이 부족합니다" << std::endl;
			system("pause");
			continue;
		}
		else if (EmptyInventory == MAX_ITEM)
		{
			std::cout << "인벤토리 공간이 부족합니다" << std::endl;
			system("pause");
			continue;
		}
		CObjectManager::GetInst()->GetPlayer()->SetGold(-1*mItem[ItemIndex]->GetBuy());
		CGameManager::GetInst()->GetInventory()->StackItem(mItem[ItemIndex]->GetType(), ItemIndex);
		CGameManager::GetInst()->GetInventory()->AddInventoryCounter();
	}
}
