#pragma once
#include "GameInfo.h"

class CStore
{
public:
	CStore();
	~CStore();
private:
	EStoreType mType;
	class CItem* mItem[MAX_ITEM] = {};
public:
	bool Init(EStoreType);
	void Run();
	void SellRun();

};

