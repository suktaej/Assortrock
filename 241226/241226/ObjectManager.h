#pragma once
#include "GameInfo.h"

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();
	static CObjectManager* mInst;
public:
	static CObjectManager* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CObjectManager;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	std::list<class CObject*> mObjList;
	//���� �� ��� ������Ʈ�� ����
public:
	template<typename T>
	T* CreateObj()
	{
		T* Obj = new T;
	
		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		mObjList.emplace_back(Obj);
		return Obj;
	}
	//���ø� ������ header�� �ۼ�
	//T�� �ݵ�� Obejct�� ��ӹ޾ƾ� ��
	bool Init();
	void Output(char* OutputBuffer);
	void Update(float DeltaTime);
};

