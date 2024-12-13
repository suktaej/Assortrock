#include "Store.h"
#include "Inventory.h"

//FItem gStoreWeapon[3];
//FItem gStoreArmor[3];
// ������ Ÿ���� 2���� �迭�� ����
FItem* gStore[static_cast<int>(EItemType::Item_End)][3] = {}; //������ �迭�� ������ ����?

//FItem* CreateItem(const char* Name, EItemType Type, int Option, int Buy, int Sell)
//{
//	FItem* Item = new FItem;
////	if (Item) {
//		strcpy_s(Item->Name, Name);
//		Item->Type = Type;
//		Item->Option = Option;
//		Item->Buy = Buy;
//		Item->Sell = Sell;
////	}
////	else
////		std::cout << "������ ���� ����:" << Name << std::endl;
//	return Item;
//}
bool InitStore2()
{
	FILE* File = nullptr;
	int ArmorCount = 0;
	
	fopen_s(&File, "WeaponStore.sto", "rb");
	if (File)
	{
		int WeaponCount = 0;
		
		fread(&WeaponCount, sizeof(int), 1, File);
	
		for (int i = 0;i < WeaponCount;i++)
		{
			fread(gStore[static_cast<int>(EItemType::Item_Weapon)][i], sizeof(FItem), 1, File);
		}
	}
	return true;

}

bool InitStore()
{
	FILE* File = nullptr;
	fopen_s(&File, "ItemList.lst", "rb");
	if (File)
	{
		for (int i = 0; i < static_cast<int>(EItemType::Item_End); ++i) {
			for (int j = 0; j < 3; ++j) {
				FItem* Item = new FItem;
				fread(Item, sizeof(FItem), 1, File);
				gStore[i][j] = Item;
			}
		}
		fclose(File);
		return true;
	}
	return false;
		//	gStore[static_cast<int>(EItemType::Item_Weapon)][0] = CreateItem("�ܰ�",EItemType::Item_Weapon,10,1000,500);
		//	gStore[static_cast<int>(EItemType::Item_Weapon)][1] = CreateItem("���",EItemType::Item_Weapon,50,12000,6000);
		//	gStore[static_cast<int>(EItemType::Item_Weapon)][2] = CreateItem("��հ�",EItemType::Item_Weapon,100,40000,20000);
		//	
		//	gStore[static_cast<int>(EItemType::Item_Armor)][0] = CreateItem("õ����",EItemType::Item_Armor,10,1000,500);
		//	gStore[static_cast<int>(EItemType::Item_Armor)][1] = CreateItem("���װ���",EItemType::Item_Armor,50,12000,6000);
		//	gStore[static_cast<int>(EItemType::Item_Armor)][2] = CreateItem("�Ǳݰ���",EItemType::Item_Armor,100,40000,20000);
		////	for (int i = 0; i < static_cast<int>(EItemType::Item_End); i++) {
		////		for (int j = 0; j < 3; j++) {
		////			if (gStore[i][j] != nullptr) {
		////				std::cout << "������: " << gStore[i][j]->Name << " �߰�" << std::endl;
		////			}
		////		}
		////	}
}

void DestroyStore()
{
	for(int i=0;i<static_cast<int>(EItemType::Item_End); i++)
		for (int j = 0;j < 3;j++)
		{
			delete gStore[i][j];
		}
}

void RunStore(FPlayer* Player, EItemType Type)
{
	char StoreName[32] = {};
	char OptionName[32] = {};
	
//	if (Type < EItemType::Item_Weapon || Type >= EItemType::Item_End) {
//		std::cout << "�߸��� ������ Ÿ���Դϴ�." << std::endl;
//		return;
//	}

	switch (Type)
	{
	case EItemType::Item_Weapon:
		strcpy_s(StoreName, "����");
		strcpy_s(OptionName, "���ݷ�");
		break;
	case EItemType::Item_Armor:
		strcpy_s(StoreName, "��");
		strcpy_s(OptionName, "����");
		break;
	}

	while (true)
	{
		system("cls");
		std::cout << "================== ";
		std::cout << StoreName << "����";
		std::cout << " ==================" << std::endl;

		for (int i = 0; i < 3; i++)
		{
			std::cout << i + 1 << "." << gStore[static_cast<int>(Type)][i]->Name << std::endl;
			std::cout << "���� : " << StoreName << std::endl;
			std::cout << OptionName << " : " << gStore[static_cast<int>(Type)][i]->Option << std::endl;
			std::cout << "���űݾ� : " << gStore[static_cast<int>(Type)][i]->Buy << std::endl;
			std::cout << "�Ǹűݾ� : " << gStore[static_cast<int>(Type)][i]->Sell << std::endl;
			std::cout << " ==================" << std::endl;

		}
		std::cout << "4. �ڷΰ���" << std::endl;
		std::cout << "������: " << Player->Gold << std::endl;
		std::cout << "������ ���� : ";

		int	Input;
		std::cin >> Input;

		if (4 == Input)
			return;

		else if (Input < 1 || Input > 4)
			continue;

		//1~3������ ����
		//������ ��ȣ�� �ε����� ����
		int ItemIndex = Input - 1;

		//1.�� ����
		//2.�κ��丮 ����
		//��������, ��� ��

		if (gStore[static_cast<int>(Type)][ItemIndex]->Buy > Player->Gold)
		{
			std::cout << "�������� �����մϴ�" << std::endl;
			system("pause");
			continue;
		}
		else if (gInventoryCount == INVENTORY_MAX)
		{
			std::cout << "�κ��丮 ������ �����մϴ�" << std::endl;
			system("pause");
			continue;
		}
		FItem* BuyItem = new FItem;

		memcpy_s(BuyItem, sizeof(FItem), gStore[static_cast<int>(Type)][ItemIndex], sizeof(FItem));
		//		strcpy_s(BuyItem->Name, gStore[static_cast<int>(Type)][ItemIndex]->Name);
		//		BuyItem->Type = gStore[static_cast<int>(Type)][ItemIndex]->Type;
		//		BuyItem->Option = gStore[static_cast<int>(Type)][ItemIndex]->Option;
		//		BuyItem->Buy = gStore[static_cast<int>(Type)][ItemIndex]->Buy;
		//		BuyItem->Sell = gStore[static_cast<int>(Type)][ItemIndex]->Sell;
		gInventory[gInventoryCount] = BuyItem;
		++gInventoryCount;

		Player->Gold -= BuyItem->Buy;
		std::cout << gStore[static_cast<int>(Type)][ItemIndex]->Name << " ��(��) ����" << std::endl;
		system("pause");
	}
}

