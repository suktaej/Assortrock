#pragma once
#include "GameInfo.h"
#include "ObjectManager.h"
#include "Player.h"
enum class BattleSelect
{
	Fight,
	Escape,
	End
};

class CBattle
{
	friend class CBattleManager;
private:
	CBattle();
	~CBattle();
private:
	EBattleType mType;
public:
	void Run();
	void SetBattleType(EBattleType);
	EBattleResult Fight(CPlayer*, CMonster*);
};
