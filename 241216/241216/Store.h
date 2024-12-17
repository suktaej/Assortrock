#pragma once

#include "GameInfo.h"

class CStore abstract
{
	friend class CStoreManager;

protected:
	CStore();
	virtual ~CStore();

protected:
	class CObject* mItemList[3];

public:
	virtual bool Init();
	void Run();
};

