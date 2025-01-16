#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>

#include <d3d11.h>
#include <d3dcompiler.h>

//�޸𸮸� Ž�� ���
#include <crtdbg.h>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
//���ٸ� include ���� �ܺο��� sharedPtr ��� ����
#include "Share/SharedPtr.h"

//.lib�� ��ũ�� �Ŵ� ���
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

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

struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};

struct FIndexBuffer
{
	//���ؽ� ���۳� �ε��� ���۸� ������ �� �ִ� ����ü
	ID3D11Buffer* Buffer = nullptr;

	//������ 1���� ũ��
	int Size = 0;
	//�������� ����
	int Count = 0;
	//������ ����

	//DXGI_FORMAT�� DirectX Graphics Infrastructure���� ���
	//�������� ������ ������ ������
	DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN;
	//�����迭(��� Ÿ���� �������� Ȯ���� �� �����Ƿ� ������ ������ ����)
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

//��ġ, ������ ��
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
