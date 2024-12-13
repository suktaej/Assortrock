#include "StoreManager.h"
#include "Store.h"

enum class EStoreMenu
{
	None,
	Weapon,
	Armor,
	Back
};

bool InitStoreManager()
{
	if (InitStore() == false)
		return false;

	return true;
}

void DestroyStoreManager()
{
	DestroyStore();
}

EStoreMenu Menu()
{
	system("cls");
	std::cout << "1.����" << std::endl;
	std::cout << "2.��" << std::endl;
	std::cout << "3.�ڷΰ���" << std::endl;
	std::cout << "�޴� ����: ";

	int SelectMenu = 0;
	std::cin >> SelectMenu;

	if (SelectMenu <= static_cast<int>(EStoreMenu::None) ||
		SelectMenu > static_cast<int>(EStoreMenu::Back))
		return EStoreMenu::None;

	return static_cast<EStoreMenu>(SelectMenu);
}

void RunStoreManager(FPlayer* Player)
{
	while (true)
	{
		switch (Menu())
		{
		case EStoreMenu::Weapon:
			RunStore(Player, EItemType::Item_Weapon);
			break;
		case EStoreMenu::Armor:
			RunStore(Player, EItemType::Item_Armor);
			break;
		case EStoreMenu::Back:
			return;
		}
	}
}