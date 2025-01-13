#include "GameManager.h"

DEFINITION_SINGLE(FGameManager)

FGameManager::FGameManager()
{
}

FGameManager::~FGameManager()
{
}

EMainMenu FGameManager::Menu()
{
	system("cls");
	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 점수" << std::endl;
	std::cout << "3. 종료" << std::endl;
	std::cout << "메뉴를 선택하세요 : ";
	int	Input;
	std::cin >> Input;

	if (Input <= (int)EMainMenu::None ||
		Input > (int)EMainMenu::Exit)
		return EMainMenu::None;

	return (EMainMenu)Input;
}

bool FGameManager::Init()
{
	return true;
}

void FGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Stage:
			break;
		case EMainMenu::Score:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
