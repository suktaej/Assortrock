#include "Inventory.h"

FItem* gInventory[INVENTORY_MAX];
int gInventoryCount;

bool InitInventory()
{
	return true;
}
void DestroyInventory()
{
	for(int i=0; i< gInventoryCount; i++)
	{
		delete gInventory[i];
	}
}

void RunInventory(FPlayer* Player)
{
	while (true)
	{
		system("cls");
		for (int i = 0; i < gInventoryCount;i++)
		{
			std::cout << i + 1 << "." << gInventory[i]->Name << std::endl;
			switch (gInventory[i]->Type)
			{
			case EItemType::Item_Weapon:
				std::cout << "종류: 무기" << std::endl;
				std::cout << "공격력: " << gInventory[i]->Option << std::endl;
				break;
			case EItemType::Item_Armor:
				std::cout << "종류: 방어구" << std::endl;
				std::cout << "방어력: " << gInventory[i]->Option << std::endl;
				break;
			}
			std::cout << "구매금액 : " << gInventory[i]->Buy << std::endl;
			std::cout << "판매금액 : " << gInventory[i]->Sell << std::endl;
			std::cout << " ==================" << std::endl;
		}
		std::cout << gInventoryCount + 1 << ". 뒤로가기" << std::endl;
		std::cout << "소지금:" << Player->Gold << std::endl;
		std::cout << "아이템 선택: ";
		
		int Input;
		std::cin >> Input;

		if (Input == gInventoryCount + 1)
			return;
		else if (Input <1 || Input > gInventoryCount + 1)
			continue;
	}
}
