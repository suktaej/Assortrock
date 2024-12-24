#pragma once
#include <iostream>
#include <windows.h>

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
