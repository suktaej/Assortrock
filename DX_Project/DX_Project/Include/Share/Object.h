#pragma once

#include "../GameInfo.h"

class CObject	abstract
{
public:
	CObject();
	virtual ~CObject();

protected:
	int		mRefCount = 0;
	bool	mActive = true;
	bool	mEnable = true;

public:
	int GetRefCount() const { return mRefCount; }
	bool IsActive()	const { return mActive; }
	bool IsEnable()	const { return mEnable; }
	void SetEnable(bool Enable) { mEnable = Enable; }

public:
	virtual void AddRef();
	virtual void Release();
	void Destroy();
};

