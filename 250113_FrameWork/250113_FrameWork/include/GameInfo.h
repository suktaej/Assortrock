#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Vector2D.h"

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

#define MAX_STRING 256

enum class EBulletOption
{
	Normal,
	Bound,
};

struct FRect
{
	float Left = 0.f;
	float Top = 0.f;
	float Right =0.f;
	float Bottom = 0.f;
};

struct FBullet
{
	FVector2D Pos;
	FVector2D Size;
	FVector2D MoveDir;
	float Distance = 800.f;
	EBulletOption Option = EBulletOption::Normal;
};

