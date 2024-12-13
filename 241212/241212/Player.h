#pragma once
#include "GameInfo.h"
class CPlayer
{
private:
	char mName[32] = {};
	EJob mJob = EJob::None;
	int mAttack = 0;
	int mDefense = 0;
	int mHP = 0;
	int mHPMax = 0;
	int mMP = 0;
	int mMPMax = 0;
	int mGold = 0;
	int mExp = 0;
	int mLevel = 1;
public:
	CPlayer();
	~CPlayer();
public:
	bool Init();
	void Output();
	void SetResult(int,int);
	void Resurrection();
	void SetHP(int);
	void SetGold(int);
	int GetHP();
	int GetMaxHP();
	int GetATK();
	int GetDEF();
	int GetEXP();
	int GetGold();
	bool Damage(int);
};

