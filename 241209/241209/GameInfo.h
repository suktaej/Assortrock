#pragma once
#include<iostream>

#define LEVEL_MAX 10
#define INVENTORY_MAX 10

enum class EJob : unsigned char
{
	None,
	Knight,
	Archer,
	Mage,
	End
};

struct FPlayer
{
	wchar_t	Name[32];
	EJob	Job;
	int		Attack;
	int		Defense;
	int		HP;
	int		HPMax;
	int		MP;
	int		MPMax;
	int		Level;
	int		Exp;
	int		Gold;
};

struct FMonster
{
	char	Name[32];
	int		Attack;
	int		Defense;
	int		HP;
	int		HPMax;
	int		MP;
	int		MPMax;
	int		Level;
	int		Exp;
	int		Gold;
};


