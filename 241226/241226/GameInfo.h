#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include <list>
#include <vector>
#include <unordered_map>

#define SAFE_DELETE(p) {delete p;p=nullptr;}

enum class EKey
{
	MoveKey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77,
	Fire = 32
};

enum class EObjectType
{
	Enemy,
	Player,
	PlayerBullet,
	EnemyBullet,
	Item
};

enum class ECollisionType
{
	None,
	Damage,
	Heal,
	Power,
	Score
};

enum class ESpawnType
{
	EnemyNormal,
	EnemyHard,
	EnemyBoss,
	ItemScore,
	ItemHeal,
	ItemPower
};

enum class EItemType
{
	Score,
	Heal,
	Power,
	End
};
