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
    CObjectManager::DestroyInst();  //������Ʈ ������ ����
    SAFE_DELETE(mStoreMgr);
    SAFE_DELETE(mBattleMgr);
    SAFE_DELETE(mInventory);
}

EMainMenu CGameManager::Menu()
{
    system("cls");
    std::cout << "1. ����" << std::endl;
    std::cout << "2. ����" << std::endl;
    std::cout << "3. ����" << std::endl;
    std::cout << "4. ����" << std::endl;
    std::cout << "�޴� ���� : ";

    int SelectMenu = 0;

    std::cin >> SelectMenu;

    if (SelectMenu <= static_cast<int>(EMainMenu::None) ||
        SelectMenu > static_cast<int>(EMainMenu::Exit))
        return EMainMenu::None;

    return (EMainMenu)SelectMenu;
}

bool CGameManager::Init()
{ 
    //������Ʈ ������ �ʱ�ȭ
    if (false == CObjectManager::GetInst()->Init())
        return false;

    //���������� ����
    mBattleMgr = new CBattleManager;
    //���������� ����
    mStoreMgr = new CStoreManager;
    //�κ��丮 ����
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


