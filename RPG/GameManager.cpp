#include "GameManager.h"
#include "ObjectManager.h"

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CObjectManager::DestroyInst();
}

EMainMenu CGameManager::Menu()
{
	system("cls");
	std::cout << "1.Battle" << std::endl;
	std::cout << "2.Store" << std::endl;
	std::cout << "3.Inventory" << std::endl;
	std::cout << "4.Exit" << std::endl;
	std::cout << "Select Number: ";

	int Input = 0;
	std::cin >> Input;

	if (Input <= (int)EMainMenu::None ||
		Input > (int)EMainMenu::Exit)
		return EMainMenu::None;

	return (EMainMenu)Input;
}

bool CGameManager::Init()
{
	return true;
}

void CGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Battle:
			break;
		case EMainMenu::Store:
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
