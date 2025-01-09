#include "GameManager.h"
#include "MazeManager.h"

FGameManager* FGameManager::s_Inst = nullptr;

FGameManager::FGameManager()
{
}

FGameManager::~FGameManager()
{
}

EMainMenu FGameManager::Menu()
{
	system("cls");
	std::cout << "1. 미로" << std::endl;
	std::cout << "2. 점수" << std::endl;
	std::cout << "3. 종료" << std::endl;
	std::cout << "메뉴를 선택하세요 : ";
	int	Input;
	std::cin >> Input;

	if (Input < (int)EMainMenu::None ||
		Input >(int)EMainMenu::Exit)
		return EMainMenu::None;

	return (EMainMenu)Input;
}

bool FGameManager::Init()
{
	if (!FMazeManager::GetInst()->Init())
		return false;

    return true;
}

void FGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Maze:
			FMazeManager::GetInst()->Run();
			break;
		case EMainMenu::Score:
			FMazeManager::GetInst()->RunScore();
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
