#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>

//메모리릭 탐색 헤더
#include <crtdbg.h>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix.h"
//별다른 include 없이 외부에서 sharedPtr 사용 가능
#include "Share/SharedPtr.h"

//.lib를 링크를 거는 기능
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr;}
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr;}
#define SAFE_RELEASE(p) if(p) {p->Release();}

#define	DEFINITION_SINGLE(Type) Type* Type::mInst = nullptr;

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
	unsigned int Width = 0;
	unsigned int Height = 0;
};

struct FVertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
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
	//버텍스 버퍼나 인덱스 버퍼를 생성할 수 있는 구조체
	ID3D11Buffer* Buffer = nullptr;
	//데이터 1개의 크기
	int Size = 0;
	//데이터의 개수
	int Count = 0;
	//데이터 포맷

	//DXGI_FORMAT은 DirectX Graphics Infrastructure에서 사용
	//데이터의 형식을 정의한 열거형
	DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN;
	//동적배열(어떠한 타입이 들어오는지 확정할 수 없으므로 임의의 포인터 변수)
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

//위치, 정점의 색
struct FVertexColor
{
	FVector3D Pos;
	FVector4D Color;

	FVertexColor()
	{
	}

	FVertexColor(const FVector3D& _Pos, const FVector4D& _Color)
		: Pos(_Pos), Color(_Color)
	{
	}
	FVertexColor(float x, float y, float z, float r, float g, float b, float a)
		: Pos(x, y, z), Color(r, g, b, a)
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
	Sphere2D,
	OBB2D
};

struct FAABB2D
{
	FVector2D	Min;
	FVector2D	Max;
};

struct FOBB2D
{
	FVector2D Center;			//중점
	FVector2D Axis[2];			//x,y축
	FVector2D HalfSize;			//x,y축 상자크기의 절반
};
