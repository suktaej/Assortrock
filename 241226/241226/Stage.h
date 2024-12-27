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
	//������ ������Ʈ���� �������
	int mCountX= 15;
	int mCountY= 15;
	void ComputeStageInfo();
	LARGE_INTEGER mTime;	//���� ��
	LARGE_INTEGER mSecond;	//�ʴ� �带 ��
	float mDeltaTime = 0.f;	//Delta Time
	float mStageTime = 0.f; //���������� Ȱ��ȭ �� �ð�

	char* mOutputBuffer;
public:
	bool Init(const char* FileName);
	void Run();
	//void Update(float DeltaTime);
	
	int GetStageCountX() { return mCountX; }
	int GetStageCountY() { return mCountY; }
};

