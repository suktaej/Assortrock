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
	virtual bool Damage(int Dmg);	//반환값(bool)은 생존여부
	virtual int GetDamage();

	void SetPos(const COORD& Pos) { mPos = Pos; }
	void SetPos(short x, short y) { mPos.X = x; mPos.Y = y; }

	bool GetActive() { return mActive; }

	const COORD& GetPos() const { return mPos; }

	EObjectType GetType() { return mType; }
	void SetType(EObjectType Type) { mType = Type; }
};

