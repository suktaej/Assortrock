#include "ObjectManager.h"

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
    for (int i = 0;i < mObjectCount;i++)
        SAFE_DELETE(mObjectList[i]);

    delete mPlayer;
    mPlayer = nullptr;
}

bool CObjectManager::Init()
{
    return true;
}

void CObjectManager::Output()
{
}

void CObjectManager::CreateMonsterLsit()
{
}

void CObjectManager::CreateItemList()
{
}
