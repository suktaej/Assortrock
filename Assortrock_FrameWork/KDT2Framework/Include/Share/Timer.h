#pragma once

#include "../GameInfo.h"

class CTimer
{
	friend class CGameManager;

private:
	static LARGE_INTEGER	mSecond;
	static LARGE_INTEGER	mTime;
	static float	mDeltaTime;

private:
	static void Init();
	static float Update();

public:
	static float GetDeltaTime();
};

