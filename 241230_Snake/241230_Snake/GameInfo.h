#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <vector>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr;}

#define	DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type*	mInst;\
public:\
	static Type* GetInst()\
	{\
		if(nullptr == mInst)\
			mInst = new Type;\
		return mInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(mInst);\
	}

#define	DEFINITION_SINGLE(Type) Type* Type::mInst = nullptr;

namespace EKey
{
	enum Type
	{
		MoveKey = 224,
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77
	};
}

