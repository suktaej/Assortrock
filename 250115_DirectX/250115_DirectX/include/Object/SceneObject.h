#pragma once
#include "../Share/Object.h"
class CSceneObject :
    public CObject
{
    friend class CScene;
protected:
    CSceneObject();
    virtual ~CSceneObject();
    //씬 오브젝트는 복사해서 사용할 일이 많음
    CSceneObject(const CSceneObject& Obj) {}
    CSceneObject(CSceneObject&& Obj) {}
protected:
	//모든 오브젝트는 본인이 포함된 씬을 알고 있어야 함
	class CScene* m_Scene = nullptr;
	//씬 오브젝트의 이름정보
	std::string m_Name;
	//계층구조를 위해 루트 컴포넌트를 확인하기 위한 자료
	//자식 노드들이 동시에 이동할 수 있도록
	CSharedPtr<class CSceneComponent> m_RootComponent;
public:
	//포함 된 씬을 반환하기 위함
	class CScene* GetScene() const { return m_Scene; }
	//c_str() : std::string 타입의 문자열 포인터 반환
	const char* GetName() { return m_Name.c_str(); }
	void SetName(const std::string& Name) { m_Name = Name; }
public:
	void SetRootComponent(class CSceneComponent* Root);
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
};

