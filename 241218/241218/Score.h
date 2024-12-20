#pragma once
#include "Gameinfo.h"
#include "Maze.h"
class CScore
{
public:
	CScore();
	~CScore();
private:
	FScore	mScoreArray[5] = {};
	int		mScoreCount = 0;
public:
	void SetScore(CMaze*);
	void OutputScore();
	void SetScoreCounter(int Input) { mScoreCount = Input; }
};

