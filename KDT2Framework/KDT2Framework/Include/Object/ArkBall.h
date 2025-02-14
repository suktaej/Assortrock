#pragma once
#include "SceneObject.h"

class CArkBall :
    public CSceneObject
{
    friend class CScene;

protected:
    CArkBall();
    CArkBall(const CArkBall& Obj);
    CArkBall(CArkBall&& Obj);
    virtual ~CArkBall();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;
    CSharedPtr<class CColliderSphere2D>      mBody;
    CSharedPtr<class CMovementComponent>    mMovement;
    CSharedPtr<class CRotationComponent>    mRotation;

    float   mSpeed = 200.f;

public:
    void SetSpeed(float Speed) { mSpeed = Speed; }
    void SetBallCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void CollisionBall(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionBallEnd(class CColliderBase* Dest);
    void ReflectionFunc(const FVector3D& BallAxis, const FVector3D& NormalLine);
    FVector2D& NormalLineCal(const FVector3D& HitPoint, CColliderBase* Dest);
};

