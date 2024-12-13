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
				std::cout << "����: ����" << std::endl;
				std::cout << "���ݷ�: " << gInventory[i]->Option << std::endl;
				break;
			case EItemType::Item_Armor:
				std::cout << "����: ��" << std::endl;
				std::cout << "����: " << gInventory[i]->Option << std::endl;
				break;
			}
			std::cout << "���űݾ� : " << gInventory[i]->Buy << std::endl;
			std::cout << "�Ǹűݾ� : " << gInventory[i]->Sell << std::endl;
			std::cout << " ==================" << std::endl;
		}
		std::cout << gInventoryCount + 1 << ". �ڷΰ���" << std::endl;
		std::cout << "������:" << Player->Gold << std::endl;
		std::cout << "������ ����: ";
		
		int Input;
		std::cin >> Input;

		if (Input == gInventoryCount + 1)
			return;
		else if (Input <1 || Input > gInventoryCount + 1)
			continue;
	}
}
