#pragma once
#include "GameInfo.h"
class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();
	static CObjectManager* s_Inst;
public:
	static CObjectManager* GetInst()
	{
		if (nullptr == s_Inst)
			s_Inst = new CObjectManager;
		return s_Inst;
	}
	static void DestroyInst()
	{
		delete s_Inst;
		s_Inst = nullptr;
	}
private:
	std::list<class CObject*> m_ObjList;
public:
	bool Init();
	void Update(float DeltaTime);
	void Output(char* Buffer);
public:
	template<typename T>
	T* CreateObj()
	{
		T* Obj = new T;

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			Obj = nullptr;
		}
		m_ObjList.emplace_back(Obj);

		return Obj;
	}
};

