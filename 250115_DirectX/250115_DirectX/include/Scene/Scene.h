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
	std::list<CSharedPtr<class CSceneObject>> mObjList;
	//���� �����ϴ� ��ǲ
	class CInput* mInput = nullptr;
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

	virtual void Input(float DeltaTime);
public:
	class CInput* GetInput() const { return mInput; }
public:
	template<typename T>
	T* CreateObj(const std::string& Name)
	{
		T* Obj = new T;

		Obj->mScene = this;
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}
		mObjList.push_back(Obj);

		return Obj;
	}
};

