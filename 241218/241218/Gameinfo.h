#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

#define SAFE_DELETE(p) if(p) {delete p;p=nullptr;}

enum class ETileType :unsigned char
{
	Road,
	Wall,
	Start,
	Goal,
	Item,
	Trap,
	HP
};

enum class Ekey
{
	Movekey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};

enum class EObjectType
{
	Item,
	Trap
};

struct FScore
{
	__int64 Time;
	int Score;
};
