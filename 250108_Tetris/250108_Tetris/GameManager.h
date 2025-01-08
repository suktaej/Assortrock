#pragma once
#include "GameInfo.h"

class FGameManager
{
private:
	FGameManager();
	~FGameManager();
	static FGameManager* s_Inst;
public:
	static FGameManager* GetInst()
	{
		if (s_Inst == nullptr)
			s_Inst = new FGameManager;
		return s_Inst;
	}
	static void DestroyInst()
	{
		delete s_Inst;
		s_Inst = nullptr;
	}
private:
	EMenu Menu();
public:
	bool Init();
	void Run();
};

