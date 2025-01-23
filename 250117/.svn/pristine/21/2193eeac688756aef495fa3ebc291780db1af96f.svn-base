#include "Timer.h"

LARGE_INTEGER CTimer::mSecond = {};
LARGE_INTEGER CTimer::mTime = {};
float CTimer::mDeltaTime = 0.f;

void CTimer::Init()
{
	QueryPerformanceFrequency(&mSecond);
	QueryPerformanceCounter(&mTime);
}

float CTimer::Update()
{
	LARGE_INTEGER	Time;

	QueryPerformanceCounter(&Time);

	mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

	mTime = Time;

	return mDeltaTime;
}

float CTimer::GetDeltaTime()
{
	return mDeltaTime;
}
