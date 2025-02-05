#pragma once
#include "../GameInfo.h"

class CScene abstract
{
	friend class CSceneManager;
protected:
	CScene();
	virtual ~CScene();
protected:
	//오브젝트 목록
	//이는 씬이 끝날 때까지 보관하는 오브젝트 외에
	//중간 삽입삭제가 일어날 수 있기 때문에 리스트 사용
	std::list<CSharedPtr<class CSceneObject>> mObjList;
	//씬이 포함하는 인풋
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

	//업데이트 시 영향을 받는 객체가 있다면 
	//영향을 주는 객체를 먼저 업데이트 후 업데이트 필요
	//업데이트 선후관계를 위한 함수 생성
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
	
	//오브젝트 리스트의 T포인터 타입으로 형변환
	//다이나믹캐스트이므로 존재할 경우만 반환
	//nullptr이면 무시
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
