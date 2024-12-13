#include "GameInfo.h"

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

bool InitItem(void)
{
	ItemList[static_cast<int>(EItemType::Item_Weapon)][0] = CreateItem("´Ü°Ë",EItemType::Item_Weapon,10,1000,500);
	ItemList[static_cast<int>(EItemType::Item_Weapon)][1] = CreateItem("Àå°Ë",EItemType::Item_Weapon,50,12000,6000);
	ItemList[static_cast<int>(EItemType::Item_Weapon)][2] = CreateItem("¾ç¼Õ°Ë",EItemType::Item_Weapon,100,40000,20000);
	
	ItemList[static_cast<int>(EItemType::Item_Armor)][0] = CreateItem("Ãµ°©¿Ê",EItemType::Item_Armor,10,1000,500);
	ItemList[static_cast<int>(EItemType::Item_Armor)][1] = CreateItem("°¡Á×°©¿Ê",EItemType::Item_Armor,50,12000,6000);
	ItemList[static_cast<int>(EItemType::Item_Armor)][2] = CreateItem("ÆÇ±Ý°©¿Ê",EItemType::Item_Armor,100,40000,20000);

	FILE* File = nullptr;

	fopen_s(&File, "ItemList.lst", "wb");
	if (File)
	{
		for (int i = 0; i < static_cast<int>(EItemType::Item_End); ++i) 
		{
			for (int j = 0; j < 3; ++j) {
				if (ItemList[i][j] != nullptr) { // nullptr Ã¼Å©
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

	strcpy_s(WeaponStore[0].Name, "´Ü°Ë");
	WeaponStore[0].Type = EItemType::Item_Weapon;
	WeaponStore[0].Option = 10;
	WeaponStore[0].Buy = 10;
	WeaponStore[0].Sell = 10;
	
	strcpy_s(WeaponStore[1].Name, "Àå°Ë");
	WeaponStore[1].Type = EItemType::Item_Weapon;
	WeaponStore[1].Option = 20;
	WeaponStore[1].Buy = 20;
	WeaponStore[1].Sell = 20;
	
	strcpy_s(WeaponStore[2].Name, "¾ç¼Õ°Ë");
	WeaponStore[2].Type = EItemType::Item_Weapon;
	WeaponStore[2].Option = 30;
	WeaponStore[2].Buy = 30;
	WeaponStore[2].Sell = 30;
	
	strcpy_s(ArmorStore[0].Name, "Ãµ°©¿Ê");
	ArmorStore[2].Type = EItemType::Item_Armor;
	ArmorStore[2].Option = 100;
	ArmorStore[2].Buy = 100;
	ArmorStore[2].Sell = 100;
	
	strcpy_s(ArmorStore[1].Name, "°¡Á×°©¿Ê");
	ArmorStore[1].Type = EItemType::Item_Armor;
	ArmorStore[1].Option = 100;
	ArmorStore[1].Buy = 100;
	ArmorStore[1].Sell = 100;
	
	strcpy_s(ArmorStore[2].Name, "ÆÇ±Ý°©¿Ê");
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
