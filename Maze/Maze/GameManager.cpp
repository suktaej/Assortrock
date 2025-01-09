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
	std::cout << "1. �̷�" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "�޴��� �����ϼ��� : ";
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
