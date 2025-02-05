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
	class CScene* mScene = nullptr;
	class CSceneObject* mOwnerObject = nullptr;
	std::string mName;
public:
	class CScene* GetScene() const { return mScene; }
	const char* GetName() { return mName.c_str(); }
	CSceneObject* GetOwner()	const { return mOwnerObject; }
	void SetName(const std::string& Name) { mName = Name; }
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
