#pragma once
#include "Gameinfo.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();
protected:
	COORD mPos;	//��� ��ǥ�� �����ϱ� ���� ����
public:
	virtual bool Init();
	virtual void Output(char* OutBuffer,int CountX);
	virtual void Update();
	const COORD& GetPos() const { return mPos; }
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	void SetPos(const COORD& Pos) { mPos = Pos; }
};

