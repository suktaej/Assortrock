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
			//Time���� ū ���� ���� ��� ScoreIndex�� -1 ����
			//�迭�� ������ ����� �ʵ��� ������ ��
			if (mScoreArray[i].Time > Time)
			{
				ScoreIndex = i;
				break;
			}
		}

		//�迭�� �Էµ� �ð����� ū �ð��� ���ٸ�
		if (ScoreIndex == -1)
		{
			ScoreIndex = mScoreCount;
			if (ScoreIndex >= 5)
				ScoreIndex = -1;
		}
	}

	if (ScoreIndex != -1)
	{
		//���� ������ �� �ε������� ���� �������� 1ĭ�� �б�
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
	std::cout << "�ð�\t����" << std::endl;

	for (int i = 0; i < mScoreCount; ++i)
	{
		__int64 Minute = mScoreArray[i].Time / 60;
		__int64 Second = mScoreArray[i].Time % 60;

		std::cout << Minute << ":" << Second << "\t" <<
			mScoreArray[i].Score << std::endl;
	}
	system("pause");
}
