#include "GameManager.h"
#include "MazeManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

bool CGameManager::Init()
{
    CMazeManager::GetInst()->Init();
    return true;
}

void CGameManager::Run()
{
    while (true)
    {
        switch (Menu())
        {
        case EMainMenu::Maze:
			CMazeManager::GetInst()->Run();
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
	std::cout << "1.미로 선택"<<std::endl;
	std::cout << "2.점수 확인"<<std::endl;
	std::cout << "3.종료"<<std::endl;
    int Input;
    std::cout << "메뉴 선택: ";
    std::cin >> Input;

    if (Input<(int)EMainMenu::None ||
        Input>(int)EMainMenu::Exit)
        return EMainMenu::None;

    return (EMainMenu)Input;
}
