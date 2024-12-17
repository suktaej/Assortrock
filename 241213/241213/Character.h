#pragma once
#include "Object.h"
class CCharacter : public CObject
{
public:
	CCharacter();
	~CCharacter();
protected:
	int mAttack;
	int mDefense;
	int mHP;
	int mHPMax;
	int mMP;
	int mMPMax;
	int mLevel = 1;
	int mExp = 0;
	int mGold = 10000;
public:
	bool Init();
	void Output() override;
public:
	void SetCharaterInfo(int ATK, int DEF, int HP, int MP);
};

