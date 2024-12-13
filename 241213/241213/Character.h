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
	int mLevel;
	int mExp;
	int mGold;
public:
	bool Init();
	void Output();
public:
	void SetCharaterInfo(int ATK, int DEF, int HP, int MP);
};

