#pragma once

#include "GameInfo.h"

class CObjectManager
{
private:
	class CObject* mObjectList[10];
	int				mObjectCount = 0;
	class CPlayer* mPlayer = nullptr;

public:
	class CObject* GetObject(int Index)
	{
		return mObjectList[Index];
	}

public:
	bool Init();
	void Output();

private:
	void CreateMonsterList();
	void CreateItemList();

	DECLARE_SINGLE(CObjectManager)
};

