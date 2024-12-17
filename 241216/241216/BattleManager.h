#pragma once

#include "GameInfo.h"

class CBattleManager
{
private:
	class CBattle* mBattle[3];

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CBattleManager)
};

