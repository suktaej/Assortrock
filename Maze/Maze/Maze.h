#pragma once
#include "GameInfo.h"

class FMaze
{
public:
	FMaze();
	~FMaze();
private:
	int m_Xsize;
	int m_Ysize;
	//출력용 버퍼
	char* m_Buffer;
	//2차원 배열
	ETileType** m_MazeArray = nullptr;
	COORD m_StartPos;
	COORD m_EndPos;

	int m_PrevPlayerIndex = 0;
	char m_PrevPlayerOutput;
public:
	bool Init();
	void Run();
	void Reset();
	ETileType GetTile(int x, int y) const 
	{ return m_MazeArray[y][x]; }
};

