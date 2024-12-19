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
	virtual void Output();
	virtual void Update();
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	void SetPos1(const COORD& Pos) { mPos = Pos; }

};

