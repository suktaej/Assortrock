#pragma once
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<list>
#include<assert.h>
#include<vector>

#define SAFE_DELETE(p) {delete p;p=nullptr;}

#define MAP_XSIZE 12
#define MAP_YSIZE 8//26
#define BLOCKSIZE 4

enum class EKey
{
	MoveKey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};

enum class EMenu
{
	None,
	Game,
	Score,
	Exit
};

enum class EBlockType
{
	I,
	L,
	J,
	S,
	Z,
	T,
	End
};

enum class ECollisionType
{
	None,
	RightWall,
	LeftWall,
	Floor,
	End
};

