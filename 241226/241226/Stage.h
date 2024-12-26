#pragma once
#include "GameInfo.h"
enum class ESpawnDir
{
	Down,
	Right,
	Left
};
struct FStageInfo
{
	int Time;
	EObjectType Type;
	int xPos;
	int yPos;
	ESpawnDir Dir;

};

class CStage
{
public:
	CStage();
	~CStage();
private:
	std::list<FStageInfo> mInfoList;
public:
	bool Init(const char* FileName);
	void Run();
};

