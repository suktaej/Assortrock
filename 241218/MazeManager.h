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
	__int64 mScoreArray[5] = {};
	int mScoreCount = 0;
	int Menu();
	//===아이템 저장
	class CItem* mItemArray = nullptr;
	int mItemCount = 0;
public:
	bool Init();
	void Run();
	void RunScore();
	//===리셋함수
	void ResetMaze();
};

