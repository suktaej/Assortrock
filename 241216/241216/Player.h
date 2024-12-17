#pragma once

#include "Character.h"

enum class EJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion
};

class CPlayer :
    public CCharacter
{
public:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	~CPlayer();

protected:
	EJob	mJob;
	class CSkillActive* mSkillArray[2] = {};

public:
	void SetJob(EJob Job)
	{
		mJob = Job;
	}

public:
	bool Init();
	virtual void Output();

	virtual CPlayer* Clone();
};

