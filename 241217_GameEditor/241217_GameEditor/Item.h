#pragma once

#include "Object.h"

class CItem :
    public CObject
{
public:
	CItem();
	CItem(const CItem& Obj);
	~CItem();

protected:
	EItemType	mType;
	int			mOption = 0;
	int			mBuy = 0;
	int			mSell = 0;
public:
	EItemType GetItemType() { return mType; }
public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual void Save(FILE* File);
	virtual CItem* Clone();
};

