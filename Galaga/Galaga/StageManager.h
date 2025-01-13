#pragma once
#include "Stage.h"

class CStageManager
{
private:
	CStageManager();
	~CStageManager();
	static CStageManager* s_Inst;
public:
	static CStageManager* GetInst()
	{
		if (nullptr == s_Inst)
			s_Inst = new CStageManager;
		return s_Inst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(s_Inst);
	}
private:
	std::vector<std::string> m_vecFileName;
	std::vector<std::string> m_vceName;
	CStage* m_Stage = nullptr;
	int m_Count = 0;
public:
	int Init();
	void Run();
};

