#include "GameAI.h"

CAI::CAI() {}
CAI::~CAI() {}

bool CAI::Init()
{
	for (int i = 0; i < 25;i++)
	{
		mNumber[i] = i + 1;
		mRandomNum[i] = i + 1;
	}

	for (int i = 0;i < 100;i++)
	{
		int Index1 = rand() % 25;
		int Index2 = rand() % 25;

		int Temp = mNumber[Index1];
		mNumber[Index1] = mNumber[Index2];
		mNumber[Index2] = Temp;
	}
	return true;
}

void CAI::Output()
{
	std::cout << "========AI========" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5;j++)
		{
			if (mNumber[i * 5 + j] == INT_MAX)
				std::cout << "*\t";
			else
				std::cout << mNumber[i * 5 + j] << "\t";
		}
		std::cout << std::endl;
	}
}

bool CAI::ChangeNumber(int Input)
{
	for (int i = 0;i < 25;i++)
	{
		if (mNumber[i] == Input)
		{
			mNumber[i] = INT_MAX;
			return false;
		}
	}
	return true;
}
void CAI::CheckLine()
{
	LineCount = 0;
	int Check1 = 0, Check2 = 0;
	for (int i = 0;i < 5;i++)
	{
		Check1 = 0;
		Check2 = 0;
		for (int j = 0;j < 5;j++)
		{
			if (mNumber[i * 5 + j] == INT_MAX)	Check1++;
			if (mNumber[j * 5 + i] == INT_MAX)	Check2++;
		}
		if (Check1 == 5) ++LineCount;
		if (Check2 == 5) ++LineCount;
	}

	Check1 = 0;
	for (int i = 0;i < 25;i += 6)
	{
		if (mNumber[i] == INT_MAX)
			++Check1;
	}
	if (Check1 == 5) ++LineCount;

	Check1 = 0;
	for (int i = 0;i < 20;i += 4)
	{
		if (mNumber[i] == INT_MAX)
			++Check1;
	}
	if (Check1 == 5) ++LineCount;
}

int CAI::GetLineCount()
{
	return LineCount;
}

void CAI::DeleteNumber(int Input)
{
	for (int i = 0;i < mAIRandomNumCount; i++)
	{
		if (mRandomNum[i] == Input)
		{
			mRandomNum[i] = mRandomNum[mAIRandomNumCount - 1];
			mAIRandomNumCount--;
			break;
		}
	}
}

int CAI::AINumberInput()
{
	AIInput = rand() % mAIRandomNumCount;
	return mRandomNum[AIInput];
}

//void CAI::ResetLineCount() { LineCount = 0; }
