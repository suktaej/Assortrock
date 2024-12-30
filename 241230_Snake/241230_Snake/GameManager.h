#pragma once
#include "GameInfo.h"

class CGameManager
{
	DECLARE_SINGLE(CGameManager)
private:
	class CStage* mStage = nullptr;
public:
	bool Init();
	void Run();
};
