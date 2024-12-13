#pragma once
#include "GameInfo.h"

class CStore
{
public:
	CStore();
	~CStore();
private:
	EStoreType mType;
	class CItem* mItem[3] = {};
public:
	bool Init(EStoreType);
	void Run();

};

