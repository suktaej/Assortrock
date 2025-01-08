#pragma once
#include "GameInfo.h"

class FStageManager
{
private:
	FStageManager();
	~FStageManager();
	static FStageManager* s_Inst;
public:
	static FStageManager* GetInst()
	{
		if (nullptr == s_Inst)
			s_Inst = new FStageManager;

		return s_Inst;
	}
	static void DestroyInst()
	{
		delete s_Inst;
		s_Inst = nullptr;
	}
private:
	class FStage* m_Stage = nullptr;
public:
	bool Init();
	void Run();
public:
	FStage* GetStage() { return m_Stage; }
};

