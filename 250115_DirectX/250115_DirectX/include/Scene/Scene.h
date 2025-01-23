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

