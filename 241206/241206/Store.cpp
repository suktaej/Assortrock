#include "Store.h"
#include "Inventory.h"

//FItem gStoreWeapon[3];
//FItem gStoreArmor[3];
// 포인터 타입을 2차원 배열로 선언
FItem* gStore[static_cast<int>(EItemType::Item_End)][3] = {}; //포인터 배열로 생성한 이유?

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
////		std::cout << "아이템 생성 실패:" << Name << std::endl;
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
		//	gStore[static_cast<int>(EItemType::Item_Weapon)][0] = CreateItem("단검",EItemType::Item_Weapon,10,1000,500);
		//	gStore[static_cast<int>(EItemType::Item_Weapon)][1] = CreateItem("장검",EItemType::Item_Weapon,50,12000,6000);
		//	gStore[static_cast<int>(EItemType::Item_Weapon)][2] = CreateItem("양손검",EItemType::Item_Weapon,100,40000,20000);
		//	
		//	gStore[static_cast<int>(EItemType::Item_Armor)][0] = CreateItem("천갑옷",EItemType::Item_Armor,10,1000,500);
		//	gStore[static_cast<int>(EItemType::Item_Armor)][1] = CreateItem("가죽갑옷",EItemType::Item_Armor,50,12000,6000);
		//	gStore[static_cast<int>(EItemType::Item_Armor)][2] = CreateItem("판금갑옷",EItemType::Item_Armor,100,40000,20000);
		////	for (int i = 0; i < static_cast<int>(EItemType::Item_End); i++) {
		////		for (int j = 0; j < 3; j++) {
		////			if (gStore[i][j] != nullptr) {
		////				std::cout << "아이템: " << gStore[i][j]->Name << " 추가" << std::endl;
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
//		std::cout << "잘못된 아이템 타입입니다." << std::endl;
//		return;
//	}

	switch (Type)
	{
	case EItemType::Item_Weapon:
		strcpy_s(StoreName, "무기");
		strcpy_s(OptionName, "공격력");
		break;
	case EItemType::Item_Armor:
		strcpy_s(StoreName, "방어구");
		strcpy_s(OptionName, "방어력");
		break;
	}

	while (true)
	{
		system("cls");
		std::cout << "================== ";
		std::cout << StoreName << "상점";
		std::cout << " ==================" << std::endl;

		for (int i = 0; i < 3; i++)
		{
			std::cout << i + 1 << "." << gStore[static_cast<int>(Type)][i]->Name << std::endl;
			std::cout << "종류 : " << StoreName << std::endl;
			std::cout << OptionName << " : " << gStore[static_cast<int>(Type)][i]->Option << std::endl;
			std::cout << "구매금액 : " << gStore[static_cast<int>(Type)][i]->Buy << std::endl;
			std::cout << "판매금액 : " << gStore[static_cast<int>(Type)][i]->Sell << std::endl;
			std::cout << " ==================" << std::endl;

		}
		std::cout << "4. 뒤로가기" << std::endl;
		std::cout << "보유금: " << Player->Gold << std::endl;
		std::cout << "아이템 선택 : ";

		int	Input;
		std::cin >> Input;

		if (4 == Input)
			return;

		else if (Input < 1 || Input > 4)
			continue;

		//1~3번까지 선택
		//선택한 번호를 인덱스로 생성
		int ItemIndex = Input - 1;

		//1.돈 부족
		//2.인벤토리 부족
		//직업전용, 재고 등

		if (gStore[static_cast<int>(Type)][ItemIndex]->Buy > Player->Gold)
		{
			std::cout << "보유금이 부족합니다" << std::endl;
			system("pause");
			continue;
		}
		else if (gInventoryCount == INVENTORY_MAX)
		{
			std::cout << "인벤토리 공간이 부족합니다" << std::endl;
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
		std::cout << gStore[static_cast<int>(Type)][ItemIndex]->Name << " 을(를) 구매" << std::endl;
		system("pause");
	}
}

