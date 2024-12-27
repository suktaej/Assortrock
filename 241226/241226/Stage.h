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
	ESpawnType Type;
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
	//������ ������Ʈ���� �������
	int mCountX= 15;
	int mCountY= 15;
	
	LARGE_INTEGER mTime;	//���� ��
	LARGE_INTEGER mSecond;	//�ʴ� �带 ��
	float mDeltaTime = 0.f;	//Delta Time
	float mStageTime = 0.f; //���������� Ȱ��ȭ �� �ð�

	char* mOutputBuffer;

	int mScore = 0;
private:
	void ComputeStageInfo();
public:
	bool Init(const char* FileName);
	void Run();
	
	int GetStageCountX() { return mCountX; }
	int GetStageCountY() { return mCountY; }

	int GetScore() { return mScore; }
	void SetScore(int Num) { mScore += Num; }
};

