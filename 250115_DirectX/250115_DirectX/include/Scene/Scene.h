#pragma once
#include "../GameInfo.h"

class CScene abstract
{
	friend class CSceneManager;
protected:
	CScene();
	virtual ~CScene();
protected:
	//������Ʈ ���
	//�̴� ���� ���� ������ �����ϴ� ������Ʈ �ܿ�
	//�߰� ���Ի����� �Ͼ �� �ֱ� ������ ����Ʈ ���
	std::list<CSharedPtr<class CSceneObject>> m_ObjList;
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);

	//������Ʈ �� ������ �޴� ��ü�� �ִٸ� 
	//������ �ִ� ��ü�� ���� ������Ʈ �� ������Ʈ �ʿ�
	//������Ʈ ���İ��踦 ���� �Լ� ����
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual void Collision(float DeltaTime);
public:
	template<typename T>
	T* CreateObj(const std::string& Name)
	{
		T* Obj = new T;

		Obj->m_Scene = This;
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}
		m_ObjLlist.push_back(Obj);

		return Obj;
	}
};

