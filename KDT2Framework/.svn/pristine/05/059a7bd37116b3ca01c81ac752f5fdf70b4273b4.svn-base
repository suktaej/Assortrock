#pragma once

#include "SceneObject.h"

enum ETalonRState
{
    Expansion,
    Maintain,
    Reduction
};

class CTalonR :
    public CSceneObject
{
    friend class CScene;

protected:
    CTalonR();
    CTalonR(const CTalonR& Obj);
    CTalonR(CTalonR&& Obj);
    virtual ~CTalonR();

protected:
    CSharedPtr<class CStaticMeshComponent>  mMesh;
    float   mSpeed = 2.f;
    ETalonRState    mState = ETalonRState::Expansion;
    CSharedPtr<CSceneObject> mTarget;

    float           mTime = 5.f;
    float           mTimeAcc = 0.f;
    float           mReadyTime = 0.3f;
    float           mRange = 0.f;
    float           mMaxRange = 4.f;
    float           mRangeLength = 2.f;

public:
    void SetTarget(CSceneObject* Target)
    {
        mTarget = Target;
    }

    void SetSpeed(float Speed)
    {
        mSpeed = Speed;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

