#pragma once
#include "GameInfo.h"

class FObjectManager
{
private:
	FObjectManager();
	~FObjectManager();
	static FObjectManager* s_Inst;
public:
	static FObjectManager* GetInst()
	{
		if (nullptr == s_Inst)
			s_Inst = new FObjectManager;
		return s_Inst;
	}
	static void DestroyInst()
	{
		delete s_Inst;
		s_Inst = nullptr;
	}
private:
	std::list<class FObject*> m_BlockList;

public:
	bool Init();
	void Update(float DeltaTime);
	void Output(char* OutputBuffer);
public:
	std::list<FObject*>& GetObjList() { return m_BlockList; }

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
		m_BlockList.emplace_back(Obj);
		return Obj;
	}
	void RemoveBlock();
};
