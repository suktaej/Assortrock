#include "StoreManager.h"
#include "Store.h"

CStoreManager::CStoreManager()
{
}

CStoreManager::~CStoreManager()
{
}

EStoreMenu CStoreManager::Menu()
{
    system("cls");
    std::cout << "1. 무기" << std::endl;
    std::cout << "2. 방어구" << std::endl;
    std::cout << "3. 뒤로가기" << std::endl;
    std::cout << "메뉴 선택 : ";

    int SelectMenu = 0;

    std::cin >> SelectMenu;

    if (SelectMenu <= static_cast<int>(EStoreMenu::None) ||
        SelectMenu > static_cast<int>(EStoreMenu::Back))
        return EStoreMenu::None;

    return (EStoreMenu)SelectMenu;
}

bool CStoreManager::Init()
{
    mStore[static_cast<int>(EStoreType::Weapon)] = new CStore;
    mStore[static_cast<int>(EStoreType::Weapon)]->Init(EStoreType::Weapon);
    mStore[static_cast<int>(EStoreType::Armor)] = new CStore;
    mStore[static_cast<int>(EStoreType::Armor)]->Init(EStoreType::Armor);
    return true;
}

void CStoreManager::Run()
{
    while (true)
    {
        switch (Menu())
        {
        case EStoreMenu::Weapon:
            mStore[static_cast<int>(EStoreType::Weapon)]->Run();
            break;
        case EStoreMenu::Armor:
            mStore[static_cast<int>(EStoreType::Armor)]->Run();
            break;
        case EStoreMenu::Back:
            return;
        }
    }
}
