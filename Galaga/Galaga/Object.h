#pragma once
#include "GameInfo.h"

enum class EObjectType
{
	Enemy,
	Player,
	PlayerBullet,
	EnemyBullet,
	Item
};

class CObject
{
	friend class CObjectManager;
public:
	CObject();
	virtual ~CObject();
protected:
	EObjectType m_Type;
	COORD m_Pos = {};
	bool m_Active = true;
public:
	EObjectType GetType() { return m_Type; }
	void SetType(EObjectType Type) { m_Type = Type; }
	bool GetActive() { return m_Active; }
	const COORD& GetPos() { return m_Pos; }
	void SetPos(short x, short y) { m_Pos.X = x; m_Pos.Y = y; }
public:
	virtual bool Damage(int Dmg);
	virtual int GetDamage();
public:
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output(char* Buffer) = 0;
	virtual ECollisionType CollisionEnable(CObject* Dest) = 0;
};

