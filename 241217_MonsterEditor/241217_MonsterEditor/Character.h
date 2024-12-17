#pragma once
#include "Object.h"

class CCharacter : public CObject 
{
public:
	CCharacter();
	CCharacter(const CCharacter& Obj);
	~CCharacter();

protected:
	int		mAttack;
	int		mDefense;
	int		mHP;
	int		mHPMax;
	int		mMP;
	int		mMPMax;
	int		mLevel = 1;
	int		mExp = 0;
	int		mGold = 10000;

public:
public:
	bool Init() override;
	void Output() override;
	void Save(FILE*) override;
	CCharacter* Clone() = 0;
};

