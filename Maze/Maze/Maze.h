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
	//��¿� ����
	char* m_Buffer;
	//2���� �迭
	ETileType** m_MazeArray = nullptr;
	COORD m_StartPos;
	COORD m_GoalPos;

	//������ ������Ʈ�� ������ �迭
	class FObject** m_ObjList = nullptr;
	int m_ObjCount = 0;
	int m_ObjCapacity = 4;
	
	//�÷��̾� ���� ��ġ��
	int m_PrevPlayerIndex = 0;
	char m_PrevPlayerOutput;
	
	int m_Score = 0;
	__int64 m_Time = 0;

public:
	bool Init();
	void Run();
	void Reset();

	void ReAlloc();
	void SwapNPop(int);

	void InfoOutput(__int64 ,class FPlayer*);
	
	int GetScore()	const { return m_Score; }
	__int64 GetTime()	const { return m_Time; }

	ETileType GetTile(int x, int y) const 
	{ return m_MazeArray[y][x]; }

};

