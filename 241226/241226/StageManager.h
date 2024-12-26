#pragma once
#include "Stage.h"
class CStageManager
{
private:
	CStageManager();
	~CStageManager();
	static CStageManager* mInst;
public:
	static CStageManager* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CStageManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	//std::vector<CStage*> mvecStage;
	//스테이지를 여러개 가지고 있을 필요는 없음
	//생성 자체는 필요시 불러오도록 구현
	CStage* mStage = nullptr;
	int mStageCount = 0;
	std::vector<std::string> mvecFileName;
public:
	bool Init();
	void Run();
};

