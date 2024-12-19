#pragma once
#include<iostream>
#include<Windows.h>

enum class EMainMenu
{
	None,
	Maze,
	Score,
	Exit
};

class CGameManager
{
private:
	CGameManager();
	~CGameManager();
	static CGameManager* mInst;
public:
	static CGameManager* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CGameManager;
		return mInst;
	}
	static void DestroyInst()
	{
		if (mInst != nullptr) 
		{
			delete mInst;
			mInst = nullptr;
		}
	}
public:
	bool Init();
	void Run();
	EMainMenu Menu();
};

