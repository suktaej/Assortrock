#pragma once
#include "GameInfo.h"
enum class ESpawnDir
{
	Down,
	Right,
	Left
};

struct FStagInfo
{
	int Time;
	int x;
	int y;
	ESpawnDir Dir;
	ESpawnType Type;
};

class CStage
{
	friend class CStageManager;
public:
	CStage();
	~CStage();
private:
	std::list<FStagInfo> m_InfoList;
	int m_Xsize = 15;
	int m_Ysize = 15;

	LARGE_INTEGER m_Time;	//현재 시간
	LARGE_INTEGER m_Second;	//초당 흐르는 시간 값

	float m_DeltaTime = 0.f;
	float m_StageTime = 0.f;
	
	char* m_Buffer;

	int m_Score = 0;
private:
	void ComputeStageInfo();
public:
	bool Init(const char*);
	void Run();
public:
	int GetX() { return m_Xsize; }
	int GetY() { return m_Ysize; }
};

