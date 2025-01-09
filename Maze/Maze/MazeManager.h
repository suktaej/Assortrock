#pragma once
#include "GameInfo.h"

class FMazeManager
{
	DECLARE_SINGLE(FMazeManager)
private:
	class FMaze* m_Maze = nullptr;
	
	FScore m_ScoreArray[5] = {};
	int m_ScoreCount = 0;
public:
	bool Init();
	void Run();
	void RunScore();
	void ScoreCal(__int64,int);
};
