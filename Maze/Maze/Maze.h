#pragma once
#include "GameInfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();
private:
	ETileType** mMazeArray = nullptr;
	int mXsize = 0;
	int mYsize = 0;
public:
	bool Init();
	bool Init(const char* FileName);
	void Output();
};

