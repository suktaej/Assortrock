#include "GameManager.h"
#include "ObjectManager.h"
#include "StoreManager.h"
#include "Inventory.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}
CGameManager::~CGameManager()
{
    CObjectManager::DestroyInst();  //오브젝트 관리자 제거
    SAFE_DELETE(mStoreMgr);
    SAFE_DELETE(mBattleMgr);
    SAFE_DELETE(mInventory);
}

EMainMenu CGameManager::Menu()
{
    system("cls");
    std::cout << "1. 전투" << std::endl;
    std::cout << "2. 상점" << std::endl;
    std::cout << "3. 가방" << std::endl;
    std::cout << "4. 종료" << std::endl;
    std::cout << "메뉴 선택 : ";

    int SelectMenu = 0;

    std::cin >> SelectMenu;

    if (SelectMenu <= static_cast<int>(EMainMenu::None) ||
        SelectMenu > static_cast<int>(EMainMenu::Exit))
        return EMainMenu::None;

    return (EMainMenu)SelectMenu;
}

bool CGameManager::Init()
{ 
    //오브젝트 관리자 초기화
    if (false == CObjectManager::GetInst()->Init())
        return false;

    //전투관리자 생성
    mBattleMgr = new CBattleManager;
    //상점관리자 생성
    mStoreMgr = new CStoreManager;
    //인벤토리 생성
    mInventory = new CInventory;

    if (false == mBattleMgr->Init())
        return false;
    if (false == mStoreMgr->Init())
        return false;
    if (false == mInventory->Init())
        return false;
    return true;
}

void CGameManager::Run()
{
    while (true)
    {
        switch (Menu())
        {
        case EMainMenu::Battle:
            mBattleMgr->Run();
            break;
        case EMainMenu::Store:
            mStoreMgr->Run();
            break;
        case EMainMenu::Inventory:
            mInventory->Run();
            break;
        case EMainMenu::Exit:
            return;
        }
    }
}


