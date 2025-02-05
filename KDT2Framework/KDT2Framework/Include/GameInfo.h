#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <string>
#include <functional>
#include <iostream>

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix.h"

#include "Share/SharedPtr.h"

// .lib 를 링크 걸어주는 기능이다.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define	DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type*	mInst;\
public:\
	static Type* GetInst()\
	{\
		if(!mInst)\
			mInst = new Type;\
		return mInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(mInst);\
	}

#define	DEFINITION_SINGLE(Type)	Type* Type::mInst = nullptr;


namespace EShaderBufferType
{
	enum Type
	{
		Vertex = 0x1,
		Pixel = 0x2,
		Hull = 0x4,
		Domain = 0x8,
		Geometry = 0x10,
		Compute = 0x20,
		Graphic = Vertex | Pixel | Hull | Domain | Geometry,
		All = Graphic | Compute
	};
}


struct FResolution
{
	unsigned int	Width = 0;
	unsigned int	Height = 0;
};

struct FVertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int			Size = 0;
	int			Count = 0;
	void* Data = nullptr;

	FVertexBuffer()
	{
	}

	~FVertexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

struct FIndexBuffer
{
	// 데이터를 저장하기 위한 버퍼
	ID3D11Buffer* Buffer = nullptr;
	// 데이터 1개의 크기
	int		Size = 0;
	// 데이터 개수
	int		Count = 0;
	// 데이터 포맷
	DXGI_FORMAT	Fmt = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer()
	{
	}

	~FIndexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

struct FVertexColor
{
	FVector3D	Pos;
	FVector4D	Color;

	FVertexColor()
	{
	}

	FVertexColor(const FVector3D& _Pos, const FVector4D& _Color)	:
		Pos(_Pos),
		Color(_Color)
	{
	}

	FVertexColor(float x, float y, float z, float r, float g, float b, float a)	:
		Pos(x, y, z),
		Color(r, g, b, a)
	{
	}
};

enum class EColliderType : unsigned char
{
	Colider2D,
	Colider3D
};

enum class EColliderShape : unsigned char
{
	AABB2D,
	Sphere2D
};

struct FAABB2D
{
	FVector2D	Min;
	FVector2D	Max;
};

namespace ECollisionChannel
{
	enum Type : unsigned char
	{
		Default,
		Player,
		Monster,
		PlayerAttack,
		MonsterAttack,
		End
	};
}

namespace ECollisionInteraction
{
	enum Type : unsigned char
	{
		Ignore,			// 충돌 무시
		Collision,		// 충돌
		End
	};
}

/*
플레이어 프로파일을 만들고 채널을 Player로 지정했다.
이때 다른 채널을 사용하는 프로파일과 충돌해야 할지 여부를
판단하기 위해서 충돌상호작용이 다른 채널과 어떻게 되어 있는지를
저장해야 한다.

1번프로파일 정보
Channel : Player
Enable : true
Iteraction[Default] = Collision;
Iteraction[Player] = Collision;
Iteraction[Monster] = Collision;
Iteraction[PlayerAttack] = Ignore;
Iteraction[MonsterAttack] = Ignore;

2번프로파일 정보
Channel : MonsterAttack
Enable : true
Iteraction[Default] = Collision;
Iteraction[Player] = Collision;
Iteraction[Monster] = Ignore;
Iteraction[PlayerAttack] = Ignore;
Iteraction[MonsterAttack] = Ignore;
*/
struct FCollisionProfile
{
	std::string		Name;
	// 현재 프로파일이 사용하는 충돌채널
	ECollisionChannel::Type	Channel = ECollisionChannel::Default;
	bool			Enable = true;
	ECollisionInteraction::Type	Interaction[ECollisionChannel::End];
};

