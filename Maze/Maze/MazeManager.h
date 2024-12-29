#pragma once
#include "GameInfo.h"

class CMazeManager
{
private:
	CMazeManager();
	~CMazeManager();
	static CMazeManager* mInst;
public:
	static CMazeManager* GetInst()
	{
		if (nullptr == mInst)
			mInst = new CMazeManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
private:
	class CMaze** mMazeArray = nullptr;
	int mMazeCount = 0;
private:
	int Menu();
public:
	bool Init();
	void Run();
};

