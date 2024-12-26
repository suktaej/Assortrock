#pragma once
#include "GameInfo.h"

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();
protected:
	COORD mPos;
public:
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output() = 0;

	void SetPos(const COORD& Pos) { mPos = Pos; }
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	const COORD& GetPos() const { return mPos; }
};

