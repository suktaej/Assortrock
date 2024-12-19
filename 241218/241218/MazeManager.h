#pragma once
#include "Gameinfo.h"
#include "Maze.h"

class CMazeManager
{
private:
	CMazeManager();
	~CMazeManager();
	static CMazeManager* mInst;
public:
	static CMazeManager* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CMazeManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	class CMaze** mMazeArray = nullptr;
	int mMazeCount = 0;
	int Menu();
public:
	bool Init();
	void Run();
};

