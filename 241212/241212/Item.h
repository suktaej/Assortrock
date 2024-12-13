#pragma once
#include "GameInfo.h"

class CItem
{
public:
	CItem();
	~CItem();
private:
	char mName[32] = {};
	EItemType mItemType;
	int mOption;
	int mBuy;
	int mSell;
public:
	bool Init(FILE* File);
	void Output();
	CItem* Clone(){ return new CItem(*this); } //this 泅 按眉狼 林家, *this 泅 按眉
public:
	int GetBuy() { return mBuy; }
	int GetSell() { return mSell; }
	int GetOption() { return mOption; }
	const char* GetName() { return mName; }
	EItemType GetType() { return mItemType; }
};

