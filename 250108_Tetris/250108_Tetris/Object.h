#pragma once
#include "GameInfo.h"

class FObject abstract
{
public:
	FObject();
	virtual ~FObject();
protected:
	COORD mPos = {MAP_XSIZE/2,1};
	float mMoveX = 0.f;
	float mMoveY = 0.f;
	float mDirX = 0.f;
	float mDirY = 0.f;
public:
	const COORD& GetPos() { return mPos; }
	void SetPos(short x, short y) { mPos.X = x, mPos.Y = y; }
	void SetDir(float x, float y) { mDirX = x, mDirY = y; }
public:
	virtual void Update(float) = 0;
	virtual bool Init() = 0;
    virtual void Output(std::vector<std::vector<char>>&) = 0;
};

