#include "Score.h"

CScore::CScore()
{
}

CScore::~CScore()
{
}

void CScore::SetScore(CMaze* mMazeArray)
{
	__int64 Time = mMazeArray->GetTime();
	int Score = mMazeArray->GetScore();

	int ScoreIndex = -1;

	if (mScoreCount == 0)
		ScoreIndex = 0;
	else
	{
		for (int i = 0; i < mScoreCount;i++)
		{
			//Time보다 큰 값이 없을 경우 ScoreIndex는 -1 유지
			//배열의 범위를 벗어나지 않도록 유지할 것
			if (mScoreArray[i].Time > Time)
			{
				ScoreIndex = i;
				break;
			}
		}

		//배열에 입력된 시간보다 큰 시간이 없다면
		if (ScoreIndex == -1)
		{
			ScoreIndex = mScoreCount;
			if (ScoreIndex >= 5)
				ScoreIndex = -1;
		}
	}

	if (ScoreIndex != -1)
	{
		//현재 점수가 들어갈 인덱스부터 뒤의 점수들을 1칸씩 밀기
		for (int i = mScoreCount - 1;i >= ScoreIndex;--i)
		{
			if (i == 4)
				break;
			mScoreArray[i + 1] = mScoreArray[i];
		}
		mScoreArray[ScoreIndex].Time = Time;
		mScoreArray[ScoreIndex].Score = Score;
		++mScoreCount;

		if (mScoreCount > 5)
			mScoreCount = 5;
	}
}

void CScore::OutputScore()
{
	system("cls");
	std::cout << "시간\t점수" << std::endl;

	for (int i = 0; i < mScoreCount; ++i)
	{
		__int64 Minute = mScoreArray[i].Time / 60;
		__int64 Second = mScoreArray[i].Time % 60;

		std::cout << Minute << ":" << Second << "\t" <<
			mScoreArray[i].Score << std::endl;
	}
	system("pause");
}
