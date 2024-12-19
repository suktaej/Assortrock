#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
enum class ETileType :unsigned char
{
	Road,
	Wall,
	Start,
	Goal,
};

enum class Ekey
{
	Movekey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};
