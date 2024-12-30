#pragma once

#include "GameInfo.h"
class CStage
{
	friend class CGameManager;

	DECLARE_SINGLE(CStage);

private:
	int mXsize = 15;
	int mYsize = 15;
	char* mOutputBuffer;

	LARGE_INTEGER mTime;
	LARGE_INTEGER mSecond;
	float mDeltaTime = 0.f;
	float mStageTime = 0.f;

	bool mDeath = false;
public:
	bool Init();
	void Run();
public:
	int GetXsize() { return mXsize; }
	int GetYsize() { return mYsize; }
	bool GetDeath() { return mDeath; }
	void SetDeath() { mDeath = true; }

};

