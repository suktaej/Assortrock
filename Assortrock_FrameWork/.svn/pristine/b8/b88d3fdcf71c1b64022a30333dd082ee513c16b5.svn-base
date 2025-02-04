#pragma once

#include "SceneObject.h"

class CTornadoBullet :
    public CSceneObject
{
    friend class CScene;

protected:
    CTornadoBullet();
    CTornadoBullet(const CTornadoBullet& Obj);
    CTornadoBullet(CTornadoBullet&& Obj);
    virtual ~CTornadoBullet();

protected:
    CSharedPtr<class CSceneComponent>  mRoot;
    CSharedPtr<class CSceneComponent>  mPivot;
    CSharedPtr<class CStaticMeshComponent>  mMesh;
    float   mSpeed = 2.f;

public:
    void SetSpeed(float Speed)
    {
        mSpeed = Speed;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

