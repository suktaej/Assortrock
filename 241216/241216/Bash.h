#pragma once
#include "SkillActive.h"
class CBash :
    public CSkillActive
{
public:
	CBash();
	CBash(const CBash& Obj);
	~CBash();

protected:

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CBash* Clone();
};

