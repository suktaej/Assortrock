#include "TalonR.h"
#include "../Component/StaticMeshComponent.h"

CTalonR::CTalonR()
{
}

CTalonR::CTalonR(const CTalonR& Obj) :
    CSceneObject(Obj)
{
}

CTalonR::CTalonR(CTalonR&& Obj) :
    CSceneObject(Obj)
{
}

CTalonR::~CTalonR()
{
}

bool CTalonR::Init()
{
    mMesh = CreateComponent<CStaticMeshComponent>();

    mMesh->SetMesh("CenterRect");
    mMesh->SetShader("ColorMeshShader");

    mMesh->SetWorldScale(0.5f, 0.5f, 1.f);

    SetRootComponent(mMesh);

    return true;
}

void CTalonR::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Pos = mMesh->GetWorldPosition();
    FVector3D   Dir = mMesh->GetAxis(EAxis::Y);

    mTimeAcc += DeltaTime;

    switch (mState)
    {
    case Expansion:
        mRange = DeltaTime / mReadyTime *
            mMaxRange;

        mMesh->SetWorldPos(Pos + Dir * mRange);

        if (mTimeAcc >= mReadyTime)
        {
            mTimeAcc -= mReadyTime;
            mState = ETalonRState::Maintain;
        }
        break;
    case Maintain:
    {
        float   Angle = mMesh->GetWorldRotation().z;

        Angle += 1080.f * DeltaTime;

        mMesh->SetWorldRotationZ(Angle);

        if (mTimeAcc >= mTime)
        {
            mTimeAcc = 0.f;
            mState = ETalonRState::Reduction;
            SetLifeTime(5.f);
        }
    }
        break;
    case Reduction:
    {
        Dir = mTarget->GetRootComponent()->GetWorldPosition() -
            mMesh->GetWorldPosition();
        Dir.Normalize();

        mMesh->SetWorldPos(Pos + Dir * 10.f * DeltaTime);
    }
        break;
    }



    /*FVector3D Pos = mRoot->GetWorldPosition();

    Pos += mRoot->GetAxis(EAxis::Y) * mSpeed * DeltaTime;

    mRoot->SetWorldPos(Pos);

    FVector3D Rot = mPivot->GetRelativeRotation();

    Rot.z += DeltaTime * 720.f;

    mPivot->SetRelativeRotationZ(Rot.z);*/
}
