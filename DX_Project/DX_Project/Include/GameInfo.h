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

// .lib �� ��ũ �ɾ��ִ� ����̴�.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
//SharedPtr Count���� �� 0�� ��� ����
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

//�ػ�
struct FResolution
{
	unsigned int	Width = 0;
	unsigned int	Height = 0;
};

//��������
struct FVertexBuffer
{
	//����Ÿ��
	ID3D11Buffer* Buffer = nullptr;
	//������ ũ��, ����
	int			Size = 0;
	int			Count = 0;
	//������ ������(� Ÿ���� ���� �𸣹Ƿ� nullptr)
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
	// �����͸� �����ϱ� ���� ����
	// DX �������� I�� �����ϴ� ���� COM��ü
	// ���������͸� ����ϰ� �����Ƿ� ��� �Ϸ� �� Release
	ID3D11Buffer* Buffer = nullptr;
	// ������ 1���� ũ��
	int		Size = 0;
	// ������ ����
	int		Count = 0;
	// ������ ����
	DXGI_FORMAT	Fmt = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer()
	{
	}
	//���Ǹ� ���� �Ҹ���
	//�����Ҵ� �� ������ ��� ����
	~FIndexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};