#include "ObjectManager.h"
#include "Item.h"

CObjectManager* CObjectManager::mInst = nullptr;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
    for (int i = 0;i < 3;i++)
    {
        SAFE_DELETE(mMonster[i]);
    }

    for (int i = 0; i < static_cast<int>(EItemType::End);i++)
    {
        for (int j = 0; j < 3;j++) 
        SAFE_DELETE(mItem[i][j]);
    }

    SAFE_DELETE(mPlayer);
}

bool CObjectManager::LoadMonster(){

    FILE* File = nullptr;
    fopen_s(&File, "MonsterList.lst", "rb");

    if (!File)
        return false;

    for (int i = 0; i < 3; i++)
    {
        mMonster[i] = new CMonster;
        mMonster[i]->Init(File);
    }
    
    fclose(File);

    return true;
}

bool CObjectManager::LoadItem()
{
    FILE* File = nullptr;
	//int ItemSize = 0;
    
    fopen_s(&File, "WeaponStore.sto", "rb");
    if (!File)
        return false;

    fread(&ItemSize, sizeof(int), 1, File);

    for (int i = 0;i < ItemSize;i++)
    {   
        CItem* Item = new CItem;
        Item->Init(File);
        mItem[static_cast<int>(EItemType::Weapon)][i] = Item;
    }
    fclose(File);
    
    fopen_s(&File, "ArmorStore.sto", "rb");
    if (!File)
        return false;

    fread(&ItemSize, sizeof(int), 1, File);
    
    for (int i = 0;i < ItemSize;i++)
    {   
        CItem* Item = new CItem;
        Item->Init(File);
        mItem[static_cast<int>(EItemType::Armor)][i] = Item;
    }
    fclose(File);

    return true;
}

bool CObjectManager::Init()
{

    mPlayer = new CPlayer;

    if (false == mPlayer->Init())
        return false;

    if (false == LoadMonster())
        return false;

    if (false == LoadItem())
        return false;
    
    return true;
}

CMonster* CObjectManager::CreateMonster(EBattleType Type)
{
    return mMonster[(int)Type]->Clone();
}

CItem* CObjectManager::GetItem(EItemType Type, int Index)
{
    return mItem[static_cast<int>(Type)][Index];
}

CItem* CObjectManager::CopyItem(EItemType Type, int Index)
{
    return mItem[static_cast<int>(Type)][Index]->Clone();
}
