#pragma once
#include "Skill.h"
class CSkillActive :
    public CSkill
{
public:
	CSkillActive();
	CSkillActive(const CSkillActive& Obj);
	~CSkillActive();

protected:
	int		mMP = 0;
	int		mAttack = 0;

public:
	int GetMP()
	{
		return mMP;
	}

	int GetAtack()
	{
		return mAttack;
	}

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CSkillActive* Clone();
};

