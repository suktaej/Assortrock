#include "StoreWeapon.h"
#include "ObjectManager.h"

CStoreWeapon::CStoreWeapon()
{
}

CStoreWeapon::~CStoreWeapon()
{
}

bool CStoreWeapon::Init()
{
    for (int i = 0; i < 3; ++i)
    {
        mItemList[i] = CObjectManager::GetInst()->GetObject(4 + i);
    }

    return true;
}
