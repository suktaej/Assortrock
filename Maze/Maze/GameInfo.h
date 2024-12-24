#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

#define SAFE_DELETE(p) if(p) {delete p;p=nullptr;}
#define MAX_STRING 128

enum class EMainMenu:unsigned char 
{
	None,
	Maze,
	Score,
	Exit
};

enum class ETileType :unsigned char
{
	Road,
	Wall,
	Start,
	Goal
};

enum class EKey
{
	MoveKey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};
