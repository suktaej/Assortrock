#pragma once
#include "../Share/Object.h"
class CSceneObject :
    public CObject
{	//오브젝트는 씬에 배치될 예정
    friend class CScene;
protected:
    CSceneObject();
    ~CSceneObject() override;
    //씬 오브젝트는 복사해서 사용할 일이 많음
	CSceneObject(const CSceneObject& Obj);
	CSceneObject(CSceneObject&& Obj);
protected:
	//모든 오브젝트는 본인이 포함된 씬을 알고 있어야 함
	class CScene* mScene = nullptr;
	//씬 오브젝트의 이름정보
	std::string mName;
	//계층구조를 위해 루트 컴포넌트를 확인하기 위한 자료
	//자식 노드들이 동시에 이동할 수 있도록
	CSharedPtr<class CSceneComponent> mRootComponent;
	float mLifeTime = 0;
public:
	//포함 된 씬을 반환하기 위함
	class CScene* GetScene() const { return mScene; }
	//c_str() : std::string 타입의 문자열 포인터 반환
	const char* GetName() { return mName.c_str(); }
	void SetName(const std::string& Name) { mName = Name; }
	void SetLifeTime(float Time) { mLifeTime = Time; }
public:
	void SetRootComponent(class CSceneComponent* Root);
	class CSceneComponent* GetRootComponent() { return mRootComponent; }
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual void Collision(float DeltaTime);
	virtual CSceneObject* Clone();
public:
	template <typename T>
	T* CreateComponent()
	{
		T* Component = new T;
		
		Component->m_Scene = mScene;
		Component->m_OwnerObject = this;

		if (!Component->Init())
		{
			SAFE_DELETE(Component);
			return nullptr;
		}

		return Component;
	};
};

