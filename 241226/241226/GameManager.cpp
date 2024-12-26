#include "GameManager.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "Map.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
    CStageManager::DestroyInst();
    CObjectManager::DestroyInst();
}

bool CGameManager::Init()
{
    if (!CStageManager::GetInst()->Init())
        return false;
    if (!CObjectManager::GetInst()->Init())
        return false;

    return true;
}

void CGameManager::Run()
{
    //CMap::GetInst()->Run();
    while (true)
    {
        switch (Menu())
        {
        case EMainMenu::Stage:
            CStageManager::GetInst()->Run();
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
    std::cout << "1.Stage" << std::endl;
    std::cout << "2.Score" << std::endl;
    std::cout << "3.Exit" << std::endl;
    std::cout << "Select Menu: ";

    int Input;
    std::cin >> Input;

    if (Input <= (int)EMainMenu::None ||
        Input > (int)EMainMenu::Exit)
        return EMainMenu::None;

    return (EMainMenu)Input;
}
