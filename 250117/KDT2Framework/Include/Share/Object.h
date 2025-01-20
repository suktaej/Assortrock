#pragma once

#include "../GameInfo.h"

class CObject	abstract
{
public:
	CObject();
	virtual ~CObject();

protected:
	int		mRefCount = 0;

public:
	virtual void AddRef();
	virtual void Release();
};

