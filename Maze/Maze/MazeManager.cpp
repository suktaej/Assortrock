#include "MazeManager.h"
#include "Maze.h"

DEFINITION_SINGLE(FMazeManager)

FMazeManager::FMazeManager() {}
FMazeManager::~FMazeManager() {}

bool FMazeManager::Init()
{
	m_Maze = new FMaze;
	m_Maze->Init();

	return true;
}

void FMazeManager::Run()
{
	m_Maze->Run();
	//���� ���� �� �ð��� ���� ��ȯ
	__int64 Time = m_Maze->GetTime();
	int Score = m_Maze->GetScore();

	ScoreCal(Time, Score);
}

void FMazeManager::RunScore()
{
	// ������ �����ش�.
	system("cls");
	std::cout << "�ð�\t����" << std::endl;

	for (int i = 0; i < m_ScoreCount; ++i)
	{
		__int64 Minute = m_ScoreArray[i].Time / 60;
		__int64 Second = m_ScoreArray[i].Time % 60;

		std::cout << Minute << ":" << Second << "\t" <<
			m_ScoreArray[i].Score << std::endl;
	}

	system("pause");
}

void FMazeManager::ScoreCal(__int64 Time,int Score)
{
	int ScoreIndex = -1;

	//������ ���ٸ� �ε����� 0
	if (m_ScoreCount == 0)
		ScoreIndex = 0;
	else
	{		//������ �����ϴ���
		for (int i = 0;i < m_ScoreCount;i++)
		{
			//�� ������ ���� �������� �� ���� ��� 
			//�ε����� �ش���ġ(i)���� ��ȯ
			//��� ���� �������� �� ������ Ŭ ���
			//if���� �����ϹǷ� �ε����� -1�� ����
			if (m_ScoreArray[i].Time > Time)
			{
				ScoreIndex = i;
				break;
			}
		}

		//������ ���ŵ��� �ʾҴٸ�
		if (ScoreIndex == -1)
		{
			//�迭�� ������ �ε����� ��ȯ
			ScoreIndex = m_ScoreCount;
			//�迭�� ��� �� �ִٸ� �ε����� -1�� ����
			if (ScoreIndex >= 5)
				ScoreIndex = -1;
		}
	}

	//�ε��� ���� �ִٸ�(�� ������ �� �۴ٸ�)
	if (ScoreIndex != -1)
	{
		//i�� �迭�� ���������� �ε������� �������� Ž��
		for (int i = m_ScoreCount - 1;i >= ScoreIndex; --i)
		{
			//
			if (i == 4)
				break;

			m_ScoreArray[i + 1] = m_ScoreArray[i];
		}
		m_ScoreArray[ScoreIndex].Time = Time;
		m_ScoreArray[ScoreIndex].Score = Score;
		++m_ScoreCount;

		if (m_ScoreCount > 5)
			m_ScoreCount = 5;
	}
}
