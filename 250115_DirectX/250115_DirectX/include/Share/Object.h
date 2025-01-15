#pragma once
#include "../GameInfo.h"

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();
protected:
	int m_RefCount = 0;
public:
	virtual void AddRef();
	virtual void Release();
};

