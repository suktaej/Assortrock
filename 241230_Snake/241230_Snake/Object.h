#pragma once
#include "GameInfo.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();
protected:
	COORD mPos = {};
	//bool mDeath = false;
	//EObjType Type;
public:
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	const COORD& GetPos() { return mPos; }
	//bool GetDeath() { return mDeath; }
	//void SetType(EObjType Type) { this->Type = Type; }
	//EObjType GetType() { return Type; }
public:
	virtual bool Init() = 0;
	//virtual void Update() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output(char* Buffer) = 0;
};

