#pragma once
#include "GameInfo.h"

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();
protected:
	COORD mPos = {};
	bool mActive = true;
	EObjectType mType;
public:
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output(char* OutputBuffer) = 0;
	virtual ECollisionType CollisionEnable(CObject* Dest) = 0;
	virtual bool Damage(int Dmg);	//��ȯ��(bool)�� ��������
	virtual int GetDamage();

	void SetPos(const COORD& Pos) { mPos = Pos; }
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }
	const COORD& GetPos() const { return mPos; }

	bool GetActive() { return mActive; }

	EObjectType GetType() { return mType; }
	void SetType(EObjectType Type) { mType = Type; }
};

