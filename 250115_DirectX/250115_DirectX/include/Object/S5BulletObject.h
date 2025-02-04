#pragma once
#include "SceneObject.h"

enum ESkill5State
{
    Expansion,
    Maintain,
    Reduction
};

class CS5BulletObject :
    public CSceneObject
{
    friend class CScene;
protected:
    CS5BulletObject();
    CS5BulletObject(const CS5BulletObject& Obj);
    CS5BulletObject(CS5BulletObject&& Obj);
    ~CS5BulletObject() override;
protected:
    CSharedPtr<class CStaticMeshComponent>  mMesh;

    CSharedPtr<class CMovementComponent>    mMovement;
    CSharedPtr<class CRotationComponent>    mRotation;

    CSharedPtr<CSceneObject> mTarget;

    ESkill5State mState = ESkill5State::Expansion;

    float mSpeed = 4.f;
    float mTime = 3.f;
    float mTimeAcc = 0.f;
    float mReadyTime = 1.f;
    float mMaxRange = 4.f;
    float mRange = 0.f;
    float mRangeLength = 2.f;
public:
    void SetSpeed(float Speed) { mSpeed = Speed; }
    void SetTarget(CSceneObject* Target) { mTarget = Target; }
public:
    bool Init() override;
    void Update(float DeltaTime) override;
    void PreUpdate(float DeltaTime) override;
};

