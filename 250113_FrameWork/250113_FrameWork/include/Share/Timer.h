#pragma once
#include "../GameInfo.h"

class CTimer
{
	friend class CGameManager;
private:
	static LARGE_INTEGER m_Second;
	static LARGE_INTEGER m_Time;
	static float m_DeltaTime;
private:
	static void Init();
	static float Update();
public:
	static float GetDeltaTime();
};

