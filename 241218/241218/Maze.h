#pragma once

#include "Gameinfo.h"

class CMaze
{
private:
	ETileType** mMazeArray = nullptr;
	//이중포인터 확인 이차원 배열 형식
	int mCountX;
	int mCountY;
public:
	CMaze();
	~CMaze();
public:
	bool Init(const char* FileName);
	void Output();
};

