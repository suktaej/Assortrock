#pragma once
#include "GameInfo.h"
#define MAX_NAMESIZE 32

enum class EObjectType : unsigned char
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
	EObjectType mObjType;
	char mName[MAX_NAMESIZE];
public:
	void SetName(const char* Name) { strcpy_s(mName, Name); }
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	//virtual CObject* Clone() abstract;
	virtual CObject* Clone() = 0;
	//순수가상함수는 선언만 해도 무관
};

