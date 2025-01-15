#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::AddRef()
{
	++m_RefCount;
}

void CObject::Release()
{
	--m_RefCount;

	if (m_RefCount == 0)
		delete this;
}
