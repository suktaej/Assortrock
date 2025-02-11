#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>

#include <crtdbg.h>

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
//SharedPtr Count감소 및 0일 경우 제거
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define	DEFINITION_SINGLE(Type)	Type* Type::mInst = nullptr;
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

//해상도
struct FResolution
{
	unsigned int	Width = 0;
	unsigned int	Height = 0;
};

//정점버퍼
struct FVertexBuffer
{
	//버퍼타입
	ID3D11Buffer* Buffer = nullptr;
	//데이터 크기, 개수
	int			Size = 0;
	int			Count = 0;
	//저장할 데이터(어떤 타입이 올지 모르므로 nullptr)
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
	// DX 변수에서 I로 시작하는 것은 COM객체
	// 공유포인터를 사용하고 있으므로 사용 완료 시 Release
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
	//편의를 위한 소멸자
	//동적할당 된 정보는 모두 삭제
	~FIndexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};