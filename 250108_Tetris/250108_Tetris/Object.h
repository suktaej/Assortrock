#pragma once
#include "GameInfo.h"

class FObject abstract
{
public:
	FObject();
	virtual ~FObject();
protected:
	COORD mPos = {XSIZE/2,0};
	bool mPlaced= false;
	float mMoveX = 0.f;
	float mMoveY = 0.f;
	float mMoveDirX = 0.f;
	float mMoveDirY = 0.f;

public:
	bool GetState() { return mPlaced; }
	const COORD& GetPos() { return mPos; }
	void SetPos(short x, short y) { mPos.X = x, mPos.Y = y; }
	void SetDir(float x, float y) { mMoveDirX = x, mMoveDirY = y; }
	void SetLock();
	void Update(float);
public:
	virtual bool Init() = 0;
	virtual void Output(char*) = 0;
};

