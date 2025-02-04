#pragma once

#include "SceneObject.h"

class CMonsterObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CMonsterObject();
    CMonsterObject(const CMonsterObject& Obj);
    CMonsterObject(CMonsterObject&& Obj);
    virtual ~CMonsterObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<CSceneObject>  mTarget;

    float           mDetectDistance = 0.f;

public:
    void SetTarget(class CSceneObject* Target)
    {
        mTarget = Target;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

