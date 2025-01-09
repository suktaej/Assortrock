#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr;}

#define	DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type*	s_Inst;\
public:\
	static Type* GetInst()\
	{\
		if(nullptr == s_Inst)\
			s_Inst = new Type;\
		return s_Inst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(s_Inst);\
	}

#define	DEFINITION_SINGLE(Type) Type* Type::s_Inst = nullptr;

enum class ETileType : unsigned char
{
	Road,
	Wall,
	Start,
	Goal,
	Score,
	Damage,
	Heal
};

enum class EKeyType
{
	MoveKey = 224,
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};

struct FScore
{
	int		Score;
	__int64	Time;
};
