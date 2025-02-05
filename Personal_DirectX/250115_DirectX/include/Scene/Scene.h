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
	class CCameraManager* mCameraManager = nullptr;
	class CSceneCollision* mCollision = nullptr;
public:
	CInput* GetInput() const { return mInput; }
	CCameraManager* GetCameraManager() const { return mCameraManager; }
	CSceneCollision* GetCollision() const { return mCollision; }
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
	
	//������Ʈ ����Ʈ�� T������ Ÿ������ ����ȯ
	//���̳���ĳ��Ʈ�̹Ƿ� ������ ��츸 ��ȯ
	//nullptr�̸� ����
	template <typename T>
	T* FindObjectFromType()
	{
		auto	iter = mObjList.begin();
		auto	iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			T* Obj = dynamic_cast<T*>((*iter).Get());

			if (Obj)
				return Obj;
		}

		return nullptr;
	}

	//template <typename T>
	//T* FindObjectFromName(const std::string& Name)
	//{
	//	auto	iter = mObjList.begin();
	//	auto	iterEnd = mObjList.end();

	//	for (; iter != iterEnd; ++iter)
	//	{
	//		if ((*iter)->GetName() == Name)
	//			return dynamic_cast<T*>((*iter).Get());
	//	}
	//	return nullptr;
	//}

	template <typename T>
	void FindObjectsFromType(
		std::list<CSharedPtr<T>>& result)
	{
		auto	iter = mObjList.begin();
		auto	iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			T* Obj = dynamic_cast<T*>((*iter).Get());

			if (Obj)
				result.push_back(Obj);
		}
	}
};
