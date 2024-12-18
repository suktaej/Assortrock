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
	Item
};

enum class Ekey
{
	Movekey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};
