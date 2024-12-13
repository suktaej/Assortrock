#pragma once
#include <iostream>
#define SAFE_DELETE(p) if(p){delete p; p=nullptr;}
#define LEVEL_MAX 10
#define MAX_ITEM 10

enum class EJob
{
	None,
	Fighter,
	Archer,
	Mage,
	End
};

enum class EBattleType: unsigned char
{
	Easy,
	Normal,
	Hard,
	End,
};

enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

enum class EBattleSelect : unsigned char
{
	None,
	Fight,
	Escape
};

enum class EItemType
{
	Weapon,
	Armor,
	End
};

enum class EStoreType 
{
	Weapon,
	Armor,
	Sell,
	End
};
//enum class EStoreType 
//{
//	Weapon,
//	Armor,
//	End
//};

enum class EEquip
{
	Weapon,
	Armor,
	End
};
