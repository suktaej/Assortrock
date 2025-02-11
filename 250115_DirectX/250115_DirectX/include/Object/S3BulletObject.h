#pragma once
#include "SceneObject.h"
class CS3BulletObject :
    public CSceneObject
{
    friend class CScene;
protected:
    CS3BulletObject();
    CS3BulletObject(const CS3BulletObject& Obj);
    CS3BulletObject(CS3BulletObject&& Obj);
    ~CS3BulletObject() override;
protected:
    CSharedPtr<class CSceneComponent>  mRoot;
    CSharedPtr<class CSceneComponent>  mPivot;
    CSharedPtr<class CStaticMeshComponent>  mMesh;
    float   mSpeed = 400.f;
public:
    void SetSpeed(float Speed) { mSpeed = Speed; }
public:
    bool Init() override;
    void Update(float DeltaTime) override;
};

