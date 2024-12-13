#pragma once

#include "GameInfo.h"

class CPlayer
{
private:
	int mNumber[25] = {};
	int LineCount = 0;
public:
	CPlayer();
	~CPlayer();
public:
	bool Init();
	void Output();
	bool ChangeNumber(int);
	void CheckLine();
	int GetLineCount();
	//void ResetLineCount();
};

