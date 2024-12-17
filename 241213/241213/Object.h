#pragma once
#include <iostream>
#define MAX_NAME 32

enum class EObjectType: unsigned char
{
	Character,
	Item
};

class CObject
{
public:
	CObject();
	virtual ~CObject();
protected:
	EObjectType mObjType;
	char mName[MAX_NAME];
public:
	void SetName(const char* Name) { strcpy_s(mName, Name); }
	virtual bool Init();
	virtual void Output();
};

