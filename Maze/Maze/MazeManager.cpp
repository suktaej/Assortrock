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
	while (true)
	{
		m_Maze->Run();
	}
}
