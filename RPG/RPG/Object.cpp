#include "Object.h"

CObject::CObject()
{
}

CObject::CObject(const CObject& Obj)
{
	*this = Obj;
}

CObject::~CObject()
{
}

bool CObject::Init()
{
	return true;
}

bool CObject::Init(FILE* File)
{
	fread(mName, sizeof(char), 32, File);
	return true;
}

void CObject::Output()
{
	std::cout << "Name: " << mName << std::endl;
}
