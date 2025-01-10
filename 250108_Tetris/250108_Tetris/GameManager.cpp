#include "GameManager.h"
#include "StageManager.h"
#include "ObjectManager.h"

FGameManager* FGameManager::s_Inst = nullptr;

FGameManager::FGameManager()
{
}

FGameManager::~FGameManager()
{
}

bool FGameManager::Init()
{
	if (!FStageManager::GetInst()->Init())
		return false;
	if (!FObjectManager::GetInst()->Init())
		return false;

	return true;
}
EMenu FGameManager::Menu()
{
	int Input;

	system("cls");

	std::cout << "1.Start" << std::endl;
	//std::cout << "2.Score" << std::endl;
	std::cout << "2.Exit" << std::endl;
	std::cout << "Select Number: ";
	std::cin >> Input;

	if (Input <= (int)EMenu::None || Input>(int)EMenu::Exit)
		return EMenu::None;

	return (EMenu)Input;
}

void FGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMenu::Game:
			FStageManager::GetInst()->Run();
			break;
		//case EMenu::Score:
		//  break;
		case EMenu::Exit:
			return;
		}
	}
}
