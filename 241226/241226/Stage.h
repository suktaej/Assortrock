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
	//생성할 오브젝트들의 정보목록
	int mCountX= 15;
	int mCountY= 15;
	void ComputeStageInfo();
	LARGE_INTEGER mTime;	//현재 값
	LARGE_INTEGER mSecond;	//초당 흐를 값
	float mDeltaTime = 0.f;	//Delta Time
	float mStageTime = 0.f; //스테이지가 활성화 된 시간

	char* mOutputBuffer;
public:
	bool Init(const char* FileName);
	void Run();
	//void Update(float DeltaTime);
	
	int GetStageCountX() { return mCountX; }
	int GetStageCountY() { return mCountY; }
};

