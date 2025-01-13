#include "Timer.h"

LARGE_INTEGER CTimer::m_Second = {};
LARGE_INTEGER CTimer::m_Time = {};
float CTimer::m_DeltaTime = 0.f;

void CTimer::Init()
{
	QueryPerformanceFrequency(&m_Second);
	QueryPerformanceCounter(&m_Time);
}

float CTimer::Update()
{
	LARGE_INTEGER Time;

	QueryPerformanceCounter(&Time);
	m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;
	return m_DeltaTime;
}

float CTimer::GetDeltaTime()
{
	return 0.0f;
}
