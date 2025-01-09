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
	//게임 종료 후 시간과 점수 반환
	__int64 Time = m_Maze->GetTime();
	int Score = m_Maze->GetScore();

	ScoreCal(Time, Score);
}

void FMazeManager::RunScore()
{
	// 점수를 보여준다.
	system("cls");
	std::cout << "시간\t점수" << std::endl;

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

	//점수가 없다면 인덱스는 0
	if (m_ScoreCount == 0)
		ScoreIndex = 0;
	else
	{		//점수가 존재하더라도
		for (int i = 0;i < m_ScoreCount;i++)
		{
			//새 점수가 기존 점수보다 더 작을 경우 
			//인덱스는 해당위치(i)값을 반환
			//모든 기존 점수보다 새 점수가 클 경우
			//if문을 무시하므로 인덱스는 -1을 유지
			if (m_ScoreArray[i].Time > Time)
			{
				ScoreIndex = i;
				break;
			}
		}

		//위에서 갱신되지 않았다면
		if (ScoreIndex == -1)
		{
			//배열의 마지막 인덱스를 반환
			ScoreIndex = m_ScoreCount;
			//배열이 모두 차 있다면 인덱스는 -1을 유지
			if (ScoreIndex >= 5)
				ScoreIndex = -1;
		}
	}

	//인덱스 값이 있다면(새 점수가 더 작다면)
	if (ScoreIndex != -1)
	{
		//i는 배열의 마지막부터 인덱스까지 역순으로 탐색
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
