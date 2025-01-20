#pragma once
#include "../Share/Object.h"

class CComponent abstract:
    public CObject
{
	friend class CScene;
	friend class CSceneObject;
protected:
	CComponent();
	virtual ~CComponent();
	CComponent(const CComponent& Obj) {}
	CComponent(CComponent&& Obj) {}
protected:
	class CScene* m_Scene = nullptr;
	class CSceneObject* m_OwnerObject = nullptr;
	std::string m_Name;
public:
	class CScene* GetScene() const { return m_Scene; }
	const char* GetName() { return m_Name.c_str(); }
	CSceneObject* GetOwner()	const { return m_OwnerObject; }
	void SetName(const std::string& Name) { m_Name = Name; }
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CComponent* Clone();
};
