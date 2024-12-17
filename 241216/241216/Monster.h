#pragma once
#include "Character.h"
class CMonster :
    public CCharacter
{
public:
	CMonster();
	CMonster(const CMonster& Obj);
	~CMonster();

public:
	bool Init();
	virtual CMonster* Clone();
};

