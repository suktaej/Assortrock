#pragma once

#include "GameInfo.h"

class CAI
{
private:
	int mNumber[25] = {};
	int LineCount = 0;
	int mRandomNum[25] = {};
	int mAIRandomNumCount = 25;
	int AIInput = 0;

public:
	CAI();
	~CAI();
	bool Init();
	void Output();
	bool ChangeNumber(int);
	void CheckLine();
	int GetLineCount();
	void DeleteNumber(int);
	int AINumberInput();
	//void ResetLineCount();
};

