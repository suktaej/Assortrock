#pragma once

#include "GameInfo.h"

enum class EObjectType	: unsigned char
{
	Character,
	Item
};


class CObject
{
public:
	CObject();
	CObject(const CObject& Obj);
	virtual ~CObject();

protected:
	EObjectType	mObjType;
	char	mName[32];

public:
	void SetName(const char* Name)
	{
		strcpy_s(mName, Name);
	}

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual void Save(FILE* File);
	virtual CObject* Clone() = 0;
};

