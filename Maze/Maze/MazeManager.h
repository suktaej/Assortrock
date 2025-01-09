#pragma once
#include "GameInfo.h"

class FMazeManager
{
	DECLARE_SINGLE(FMazeManager)
private:
	class FMaze* m_Maze = nullptr;
public:
	bool Init();
	void Run();
};
