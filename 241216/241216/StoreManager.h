#pragma once

#include "GameInfo.h"

class CStoreManager
{
private:
	class CStore* mStoreList[2];

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CStoreManager)
};

