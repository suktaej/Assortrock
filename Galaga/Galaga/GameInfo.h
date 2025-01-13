#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <Windows.h>

#define SAFE_DELETE(p) {delete p;p = nullptr;}
#define DEFINITION_SINGLE(type) type* type::s_Inst = nullptr;

enum class ESpawnType
{
	EnemyNormal,
	EnemyHard,
	Boss,
	ItemScore,
	ItemHeal,
	ItemPower
};
