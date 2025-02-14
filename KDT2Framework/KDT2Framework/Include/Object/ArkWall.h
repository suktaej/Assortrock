#pragma once

#include "SceneObject.h"

class CArkWall:
    public CSceneObject
{
    friend class CScene;

protected:
    CArkWall();
    CArkWall(const CArkWall& Obj);
    CArkWall(CArkWall&& Obj);
    virtual ~CArkWall();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;
    CSharedPtr<class CColliderOBB2D>       mBody;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void CollisionWall(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionWallEnd(class CColliderBase* Dest);
};


