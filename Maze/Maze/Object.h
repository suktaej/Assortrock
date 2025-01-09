#pragma once
#include "GameInfo.h"

class FObject
{
public:
	FObject();
	virtual ~FObject();
protected:
	COORD mPos;
public:
	const COORD& GetPos() const { return mPos; }
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	void SetPos(const COORD& Pos) { mPos = Pos; }
public:
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* Buffer, int CountX);
};

