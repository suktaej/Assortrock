#pragma once
#include "GameInfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();
private:
	ETileType** mMazeArray = nullptr;
	
	int mPosX = 0;
	int mPosY = 0;
public:
	bool Init();
	bool Init(const char* FileName);
	void Output();
};

