#include "BattleManager.h"
#include "Battle.h"

CBattleManager::CBattleManager()
{
}

CBattleManager::~CBattleManager()
{
}

EBattleMenu CBattleManager::Menu()
{
    system("cls");
    std::cout << "1. 쉬움" << std::endl;
    std::cout << "2. 보통" << std::endl;
    std::cout << "3. 어려움" << std::endl;
    std::cout << "4. 돌아가기" << std::endl;
    std::cout << "메뉴 선택 : ";

    int SelectMenu = 0;

    std::cin >> SelectMenu;

    if (SelectMenu <= static_cast<int>(EBattleMenu::None) ||
        SelectMenu > static_cast<int>(EBattleMenu::Back))
        return EBattleMenu::None;

    return (EBattleMenu)SelectMenu;
}

bool CBattleManager::Init()
{
	return true;
}

void CBattleManager::Run()
{
    CBattle* Battle = new CBattle;

    while (true)
    {
        switch (Menu())
        {
        case EBattleMenu::Easy:
            Battle->SetBattleType(EBattleType::Easy);
            Battle->Run();
            break;
        case EBattleMenu::Normal:
            Battle->SetBattleType(EBattleType::Normal);
            Battle->Run();
            break;
        case EBattleMenu::Hard:
            Battle->SetBattleType(EBattleType::Hard);
            Battle->Run();
            break;
        case EBattleMenu::Back:
            SAFE_DELETE(Battle);
            return;
        }
    }
}
