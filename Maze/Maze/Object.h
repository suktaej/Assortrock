#pragma once
#include "GameInfo.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();
protected:
	COORD mPos;
public:
	virtual bool Init();
	virtual void Update();
	virtual void Output();
	virtual void Output(char* OutBuffer,int CountX);

	void SetPos(short X, short Y) { mPos.X = X;mPos.Y = Y; }
	void SetPos(const COORD& Pos) { mPos = Pos; }
	const COORD& GetPos() { return mPos; }
};

