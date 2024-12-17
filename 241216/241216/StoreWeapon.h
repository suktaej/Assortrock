#pragma once
#include "Store.h"
class CStoreWeapon final :
    public CStore
{
	friend class CStoreManager;

private:
	CStoreWeapon();
	virtual ~CStoreWeapon();

public:
	virtual bool Init();
};

