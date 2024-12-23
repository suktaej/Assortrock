#include "BattleManager.h"

CBattleManager::CBattleManager()
{
}

CBattleManager::~CBattleManager()
{
}

EBattleType CBattleManager::Menu()
{
    system("cls");
    std::cout << "1.Easy" << std::endl;
    std::cout << "2.Normal" << std::endl;
    std::cout << "3.Hard" << std::endl;
    std::cout << "4.Back" << std::endl;
    std::cout << "Select Number: ";

    int Input;
    std::cin >> Input;

    if (Input <= (int)EBattleType::None ||
        Input > (int)EBattleType::Back)
        return EBattleType::None;
    
    return (EBattleType)Input;
}

bool CBattleManager::Init()
{
    return true;
}

void CBattleManager::Run()
{
    while (true)
    {
        switch (Menu())
        {
        case EBattleType::Easy:
            break;
        case EBattleType::Normal:
            break;
        case EBattleType::Hard:
            break;
        case EBattleType::Back:
            return;
        }
    }
}
