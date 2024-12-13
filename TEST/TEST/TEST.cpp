#include <iostream>
#pragma once
#include <iostream>

#define LEVEL_MAX 10
#define INVENTORY_MAX 10

enum class EJob : unsigned char
{
	None,
	Fighter,
	Archer,
	Mage,
	End		//끝 부분을 명시적으로 표현
};

struct FPlayer
{
	char Name[32];
	EJob Job;
	int HP;
	int HPMax;
	int Attack;
	int Defense;
	int MP;
	int MPMax;
	int Level;
	int Exp;
	int Gold;
};

struct FMonster
{
	char Name[32];
	int HP;
	int HPMax;
	int Attack;
	int Defense;
	int MP;
	int MPMax;
	int Level;
	int Exp;
	int Gold;
};

enum class EItemType
{
	Item_Weapon,
	Item_Armor,
	Item_End
};

struct FItem
{
	char Name[32];
	EItemType Type;
	int Option;
	int Buy;
	int Sell;
};

FItem* ItemList[static_cast<int>(EItemType::Item_End)][3] = {};

FItem* CreateItem(const char* Name, EItemType Type, int Option, int Buy, int Sell)
{
	FItem* Item = new FItem;

	strcpy_s(Item->Name, Name);
	Item->Type = Type;
	Item->Option = Option;
	Item->Buy = Buy;
	Item->Sell = Sell;

	return Item;
}

int main()
{
	ItemList[static_cast<int>(EItemType::Item_Weapon)][0] = CreateItem("단검", EItemType::Item_Weapon, 10, 1000, 500);
	ItemList[static_cast<int>(EItemType::Item_Weapon)][1] = CreateItem("장검", EItemType::Item_Weapon, 50, 12000, 6000);
	ItemList[static_cast<int>(EItemType::Item_Weapon)][2] = CreateItem("양손검", EItemType::Item_Weapon, 100, 40000, 20000);

	ItemList[static_cast<int>(EItemType::Item_Armor)][0] = CreateItem("천갑옷", EItemType::Item_Armor, 10, 1000, 500);
	ItemList[static_cast<int>(EItemType::Item_Armor)][1] = CreateItem("가죽갑옷", EItemType::Item_Armor, 50, 12000, 6000);
	ItemList[static_cast<int>(EItemType::Item_Armor)][2] = CreateItem("판금갑옷", EItemType::Item_Armor, 100, 40000, 20000);

	FILE* File = nullptr;

	fopen_s(&File, "ItemList.lst", "wb");
	if (File)
	{
		for (int i = 0; i < static_cast<int>(EItemType::Item_End); ++i)
		{
			for (int j = 0; j < 3; ++j) {
				if (ItemList[i][j] != nullptr) { // nullptr 체크
					fwrite(ItemList[i][j], sizeof(FItem), 1, File);
				}
			}
		}

		fclose(File);
		return true;
	}
	return false;
}
//===================================================
bool InitItem2(void)
{
	FItem WeaponStore[3] = {};
	FItem ArmorStore[3] = {};
	int WeaponCount = 3;
	int ArmorCount = 3;

	strcpy_s(WeaponStore[0].Name, "단검");
	WeaponStore[0].Type = EItemType::Item_Weapon;
	WeaponStore[0].Option = 10;
	WeaponStore[0].Buy = 10;
	WeaponStore[0].Sell = 10;

	strcpy_s(WeaponStore[1].Name, "장검");
	WeaponStore[1].Type = EItemType::Item_Weapon;
	WeaponStore[1].Option = 20;
	WeaponStore[1].Buy = 20;
	WeaponStore[1].Sell = 20;

	strcpy_s(WeaponStore[2].Name, "양손검");
	WeaponStore[2].Type = EItemType::Item_Weapon;
	WeaponStore[2].Option = 30;
	WeaponStore[2].Buy = 30;
	WeaponStore[2].Sell = 30;

	strcpy_s(ArmorStore[0].Name, "천갑옷");
	ArmorStore[2].Type = EItemType::Item_Armor;
	ArmorStore[2].Option = 100;
	ArmorStore[2].Buy = 100;
	ArmorStore[2].Sell = 100;

	strcpy_s(ArmorStore[1].Name, "가죽갑옷");
	ArmorStore[1].Type = EItemType::Item_Armor;
	ArmorStore[1].Option = 100;
	ArmorStore[1].Buy = 100;
	ArmorStore[1].Sell = 100;

	strcpy_s(ArmorStore[2].Name, "판금갑옷");
	ArmorStore[2].Type = EItemType::Item_Armor;
	ArmorStore[2].Option = 100;
	ArmorStore[2].Buy = 100;
	ArmorStore[2].Sell = 100;

	FILE* File = nullptr;
	fopen_s(&File, "WeaponStore.sto", "wb");
	if (File) {
		fwrite(&WeaponCount, sizeof(int), 1, File);
		fwrite(WeaponStore, sizeof(FItem), 3, File);
		fclose(File);
	}

	fopen_s(&File, "ArmorStore.sto", "wb");
	if (File) {
		fwrite(&ArmorCount, sizeof(int), 1, File);
		fwrite(ArmorStore, sizeof(FItem), 3, File);
		fclose(File);
		return true;
	}
	return false;
}
