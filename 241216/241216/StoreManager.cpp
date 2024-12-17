#include "StoreManager.h"
#include "StoreWeapon.h"
#include "StoreArmor.h"

DEFINITION_SINGLE(CStoreManager)

CStoreManager::CStoreManager()
{
}

CStoreManager::~CStoreManager()
{
}

bool CStoreManager::Init()
{
	mStoreList[0] = new CStoreWeapon;
	mStoreList[0]->Init();

	mStoreList[1] = new CStoreArmor;
	mStoreList[1]->Init();

	return true;
}

void CStoreManager::Run()
{
}
