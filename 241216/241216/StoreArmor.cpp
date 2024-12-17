#include "StoreArmor.h"
#include "ObjectManager.h"

CStoreArmor::CStoreArmor()
{
}

CStoreArmor::~CStoreArmor()
{
}

bool CStoreArmor::Init()
{
    for (int i = 0; i < 3; ++i)
    {
        mItemList[i] = CObjectManager::GetInst()->GetObject(7 + i);
    }

    return true;
}
