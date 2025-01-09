#pragma once
#include "GameInfo.h"
enum class EMainMenu
{
	None,
	Maze,
	Score,
	Exit
};

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
	EMainMenu Menu();

public:
	bool Init();
	void Run();
};

