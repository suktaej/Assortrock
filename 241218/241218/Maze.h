#pragma once

#include "Gameinfo.h"

class CMaze
{
private:
	ETileType** mMazeArray = nullptr;
	//���������� Ȯ�� ������ �迭 ����
	int mCountX;
	int mCountY;
public:
	CMaze();
	~CMaze();
public:
	bool Init(const char* FileName);
	void Output();
};

