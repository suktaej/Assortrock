#pragma once

#include "GameInfo.h"

class CObject
{
public:
	CObject();
	CObject(const CObject& Obj);
	virtual ~CObject();

protected:
	char	mName[32];

public:
	void SetName(const char* Name) { strcpy_s(mName, Name); }

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual void Save(FILE*);
	virtual CObject* Clone() = 0;	
	//순수가상함수 
	//별도의 정의가 필요하지 않음?
};

