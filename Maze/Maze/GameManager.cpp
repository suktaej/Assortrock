#include "GameManager.h"

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
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
		case EMainMenu::Maze:
			break;
		case EMainMenu::Score:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}

EMainMenu CGameManager::Menu()
{
	system("cls");
	std::cout << "1. �̷�" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "�޴��� �����ϼ��� : ";
	int	Input;
	std::cin >> Input;

	if(Input<(int)EMainMenu::None|| Input>(int)EMainMenu::Exit)
		return EMainMenu::None;

    return (EMainMenu)Input;
}
