#pragma once

#include "SceneObject.h"

class CArkWall:
    public CSceneObject
{
    friend class CScene;
private:
    float xSize = 32.f;
    float ySize = 1280.f;

protected:
    CArkWall();
    CArkWall(const CArkWall& Obj);
    CArkWall(CArkWall&& Obj);
    virtual ~CArkWall();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CColliderOBB2D>       mBody;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void CollisionWall(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionWallEnd(class CColliderBase* Dest);
};


