#include "S5BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"

CS5BulletObject::CS5BulletObject()
{
}

CS5BulletObject::CS5BulletObject(const CS5BulletObject& Obj) :
    CSceneObject(Obj)
{
}

CS5BulletObject::CS5BulletObject(CS5BulletObject&& Obj) :
    CSceneObject(Obj)
{
}

CS5BulletObject::~CS5BulletObject()
{
}

bool CS5BulletObject::Init()
{
    mMesh = CreateComponent<CStaticMeshComponent>();

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();

    mMovement->SetUpdateComponent(mMesh);
    mRotation->SetUpdateComponent(mMesh);

    mRotation->SetEnable(false);
    mRotation->SetVelocityInit(false);

    mRotation->SetMoveZ(1080.f);

    mMovement->SetMoveAxis(EAxis::Y);

    mMovement->SetMoveSpeed(mMaxRange / mReadyTime);

    mMesh->SetMesh("CenterRect");
    mMesh->SetShader("ColorMeshShader");

    mMesh->SetWorldScale(50.f, 50.f, 1.f);

    SetRootComponent(mMesh);

    return true;
}

void CS5BulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
    //FVector3D Pos = mMesh->GetWorldPosition();

    //Pos += mMesh->GetAxis(EAxis::Y) * mSpeed * DeltaTime;

    //mMesh->SetWorldPos(Pos);

    //FVector3D Rot = mMesh->GetRelativeRotation();
    //Rot.z += DeltaTime * 360.f;
    //mMesh->SetRelativeRotationZ(Rot.z);
}

void CS5BulletObject::PreUpdate(float DeltaTime)
{
    CSceneObject::PreUpdate(DeltaTime);

    FVector3D Pos = mMesh->GetWorldPosition();
    FVector3D Dir = mMesh->GetAxis(EAxis::Y);

    mTimeAcc += DeltaTime;

    switch (mState)
    {
    case Expansion:
        mRange = DeltaTime / mReadyTime *
            mMaxRange;

        //mMesh->SetWorldPos(Pos + Dir * mRange);

        if (mTimeAcc >= mReadyTime)
        {
            mTimeAcc -= mReadyTime;
            mState = ESkill5State::Maintain;
            mRotation->SetEnable(true);
            mMovement->SetEnable(false);
        }
        break;
    case Maintain:
    {
        /*float   Angle = mMesh->GetWorldRotation().z;

        Angle += 1080.f * DeltaTime;

        mMesh->SetWorldRotationZ(Angle);*/

        if (mTimeAcc >= mTime)
        {
            mTimeAcc = 0.f;
            mState = ESkill5State::Reduction;
            SetLifeTime(5.f);
            mRotation->SetEnable(false);
            mMovement->SetEnable(true);

            mMovement->SetMoveAxis(EAxis::None);
        }
    }
    break;
    case Reduction:
    {
        Dir = mTarget->GetRootComponent()->GetWorldPosition() -
            mMesh->GetWorldPosition();
        Dir.Normalize();

        mMovement->SetMove(Dir);

        //mMesh->SetWorldPos(Pos + Dir * 10.f * DeltaTime);
    }
    break;
    }
}
