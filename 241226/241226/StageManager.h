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
	//���������� ������ ������ ���� �ʿ�� ����
	//���� ��ü�� �ʿ�� �ҷ������� ����
	CStage* mStage = nullptr;
	int mStageCount = 0;
	std::vector<std::string> mvecFileName;
public:
	bool Init();
	void Run();
};

