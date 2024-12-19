#pragma once
#include "Gameinfo.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();
protected:
	COORD mPos;	//모든 좌표를 저장하기 위한 변수
public:
	virtual bool Init();
	virtual void Output(char* OutBuffer,int CountX);
	virtual void Update();
	const COORD& GetPos() const { return mPos; }
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	void SetPos(const COORD& Pos) { mPos = Pos; }
};

