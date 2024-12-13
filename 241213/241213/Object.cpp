#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

bool CObject::Init()
{
	std::cout << "Object init" << std::endl;
	return true;
}

void CObject::Output()
{
	std::cout << mName << std::endl;
}
