#pragma once
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<list>
#include<assert.h>

#define SAFE_DELETE(p) {delete p;p=nullptr;}

#define XSIZE 12
#define YSIZE 26

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


