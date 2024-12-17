#pragma once
#include "Character.h"
class CMonster :
    public CCharacter
{
public:
	CMonster();
	CMonster(const CMonster& Obj);
	~CMonster();
protected:
	EBattleType mBattleType;

public:
	EBattleType GetBatterType() { return mBattleType; }
	bool Init() override; 
	void Output() override;
	void Save(FILE*) override;
	CMonster* Clone();

};

