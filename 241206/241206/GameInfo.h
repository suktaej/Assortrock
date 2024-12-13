#pragma once
#include <iostream>

#define LEVEL_MAX 10
#define INVENTORY_MAX 10

enum class EJob : unsigned char
{
	None,
	Fighter,
	Archer,
	Mage,
	End		//�� �κ��� ��������� ǥ��
};

struct FPlayer
{
	char Name[32];
	EJob Job;
	int HP;
	int HPMax;
	int Attack;
	int Defense;
	int MP;
	int MPMax;
	int Level;
	int Exp;
	int Gold;
};

struct FMonster
{
	char Name[32];
	int HP;
	int HPMax;
	int Attack;
	int Defense;
	int MP;
	int MPMax;
	int Level;
	int Exp;
	int Gold;
};

enum class EItemType
{
	Item_Weapon,
	Item_Armor,
	Item_End
};

struct FItem
{
	char Name[32];
	EItemType Type;
	int Option;
	int Buy;
	int Sell;
};
