#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>

#include <d3d11.h>
#include <d3dcompiler.h>

//메모리릭 탐색 헤더
#include <crtdbg.h>

#include "Vector2D.h"

//.lib를 링크를 거는 기능
#pragma comment(lib,"d3d11.lib")
#pragma commnet(lib,"d3dcompiler.lib")
#pragma commnet(lib,"dxguid.lib")

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr;}
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr;}

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

#define SAFE_RELEASE(p) if(p) {p->Release();}

#define MAX_STRING 256

struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
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

