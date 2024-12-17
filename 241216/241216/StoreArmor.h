#pragma once
#include "Store.h"
class CStoreArmor final :
    public CStore
{
	friend class CStoreManager;

private:
	CStoreArmor();
	virtual ~CStoreArmor();

public:
	virtual bool Init();
};

