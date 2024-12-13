#pragma once
#include "GameInfo.h"

class CMonster
{
	friend class CObjectManager;
	friend class CBattle;

private:
	CMonster();
	~CMonster();
private:
	char	mName[32] = {};
	int		mAttack = 0;
	int		mDefense = 0;
	int		mHP = 0;
	int		mHPMax = 0;
	int		mMP = 0;
	int		mMPMax = 0;
	int		mLevel = 0;
	int		mExp = 0;
	int		mGold = 10000;
public:
	bool Init(FILE*);
	void Output();
	bool Damage(int);
	void SetHP(int);
	int GetHP();
	int GetATK();
	int GetDEF();
	int GetEXP();
	int GetGold();
	char* GetName();
	CMonster* Clone();
	//자신을 복제한 새로운 몬스터 생성
	//복사생성자 사용
};

