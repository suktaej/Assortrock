#pragma once

#include "SceneObject.h"

class CArkBlock:
    public CSceneObject
{
    friend class CScene;

protected:
    CArkBlock();
    CArkBlock(const CArkBlock& Obj);
    CArkBlock(CArkBlock&& Obj);
    virtual ~CArkBlock();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;
    int mHP = 2;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    virtual float Damage(float Attack, CSceneObject* Obj);

private:
    void CollisionBall(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionBallEnd(class CColliderBase* Dest);
};


