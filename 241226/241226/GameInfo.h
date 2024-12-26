#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

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
	Right = 77
};

enum class ETile
{
	Space,
	Wall
};

enum class EObjectType
{
	EnemyNormal,
	EnemyHard,
	Boss
};
