#include "GameManager.h"

enum class EMainMenu
{
	None,
	Battle,
	Store,
	Inventory,
	Exit
};

bool InitJob(FPlayer* Player)
{
	std::cout << "Name : ";
	std::wcin >> Player->Name;

	while (true)
	{
		std::cout << "1. 기사" << std::endl;
		std::cout << "2. 궁수" << std::endl;
		std::cout << "3. 마법사" << std::endl;
		std::cout << "직업 선택 : ";

		int Input = 0;
		std::cin >> Input;

		if (static_cast<int>(EJob::None) >= Input ||
			static_cast<int>(EJob::End) <= Input)
			continue;

		Player->Job = static_cast<EJob>(Input);
		break;
	}

	switch (Player->Job)
	{
	case EJob::Knight:
		Player->Attack = 40;
		Player->Defense = 20;
		Player->HP = 500;
		Player->HPMax = 500;
		Player->MP = 100;
		Player->MPMax = 100;
		break;
	case EJob::Archer:
		Player->Attack = 50;
		Player->Defense = 15;
		Player->HP = 400;
		Player->HPMax = 400;
		Player->MP = 200;
		Player->MPMax = 200;
		break;
	case EJob::Mage:
		Player->Attack = 60;
		Player->Defense = 10;
		Player->HP = 300;
		Player->HPMax = 300;
		Player->MP = 300;
		Player->MPMax = 300;
		break;
	}
	Player->Level = 1;
	Player->Exp = 0;
	Player->Gold = 10000;
}

bool Init(FPlayer* Player)
{
	if (InitJob(Player) == false)
		return false;

	if (InitBattle() == false)
		return false;

	if (InitStoreManager() == false)
		return false;

	return true;
}

void Destroy(void)
{
}

EMainMenu Menu()
{
	system("cls");
	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 상점" << std::endl;
	std::cout << "3. 가방" << std::endl;
	std::cout << "4. 종료" << std::endl;
	std::cout << "메뉴 선택 : ";

	int SelectMenu = 0;

	std::cin >> SelectMenu;

	if (SelectMenu <= static_cast<int>(EMainMenu::None) ||
		SelectMenu > static_cast<int>(EMainMenu::Exit))
		return EMainMenu::None;

	return (EMainMenu)SelectMenu;
}

void Run(FPlayer* Player)
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Battle:
			RunBattle(Player);
			break;
		case EMainMenu::Store:
			RunStoreManager(Player);
			break;
		case EMainMenu::Inventory:
			RunInventory(player);
			break;
		case EMainMenu::Exit:
			break;
		}
	}
}