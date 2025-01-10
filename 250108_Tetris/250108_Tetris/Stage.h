#pragma once
#include "GameInfo.h"

class FStage
{
public:
	FStage();
	~FStage();
private:
	//char* m_OutputBuffer;
	const int k_Xsize = MAP_XSIZE;
	//º®¸é:2 ¸Ê:10
	const int k_Ysize = MAP_YSIZE;
	//º®¸é:2 ¸Ê:20 »ó´Ü °ø°£:4 
	//char Map[k_Ysize][k_Xsize];
	std::vector<std::vector<char>> m_Map;

	LARGE_INTEGER m_Time;
	LARGE_INTEGER m_Second;
	float m_DeltaTime = 0.f;
	float m_StageTime = 0.f;

	bool m_BlockActive = false;

	int m_LineCounter = k_Xsize-2;

	int m_Score = 0;
public:
	bool Init();
	void Run();
	void Output();
public:	
	ECollisionType CheckCollison(class FObject*,int);
	void LockBlock(FObject*);
	void MapReset();
	bool LineClear();
public:
	int GetXsize() { return k_Xsize; }
	int GetYsize() { return k_Ysize; }
	char GetBlock(int y, int x) { return m_Map[x][y]; }
	void SetActive() { m_BlockActive = true; }

	void HideCursor();
};
