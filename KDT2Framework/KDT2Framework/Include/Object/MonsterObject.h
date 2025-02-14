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
    CSharedPtr<class CSpriteComponent>  mRoot;
    //CSharedPtr<class CStaticMeshComponent>  mRoot;
    //CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<class CColliderSphere2D>       mBody;
    //CSharedPtr<class CColliderOBB2D>       mBody;
    CSharedPtr<CSceneObject>  mTarget;

    float           mDetectDistance = 0.f;

    int             mHP = 5;

public:
    void SetTarget(class CSceneObject* Target)
    {
        mTarget = Target;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    virtual float Damage(float Attack, CSceneObject* Obj);

private:
    void CollisionMonster(const FVector3D& HitPoint,
        class CColliderBase* Dest);
    void CollisionMonsterEnd(class CColliderBase* Dest);
};

