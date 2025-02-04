#pragma once

#include "SceneObject.h"

class CBulletObject :
    public CSceneObject
{
    friend class CScene;
protected:
    CBulletObject();
    CBulletObject(const CBulletObject& Obj);
    CBulletObject(CBulletObject&& Obj);
    virtual ~CBulletObject();
protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CMovementComponent>  mMovement;
    float   mSpeed = 400.f;
public:
    void SetSpeed(float Speed) { mSpeed = Speed; }
public:
    bool Init() override;
    void Update(float DeltaTime) override;
};


