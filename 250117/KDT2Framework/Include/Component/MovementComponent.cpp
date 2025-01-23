#include "MovementComponent.h"
#include "SceneComponent.h"

CMovementComponent::CMovementComponent()
{
}

CMovementComponent::CMovementComponent(
    const CMovementComponent& Com)  :
    CComponent(Com)
{
}

CMovementComponent::CMovementComponent(CMovementComponent&& Com) :
    CComponent(Com)
{
}

CMovementComponent::~CMovementComponent()
{
}

void CMovementComponent::SetUpdateComponent(CSceneComponent* Target)
{
    mUpdateComponent = Target;
}

bool CMovementComponent::Init()
{
    if (!CComponent::Init())
        return false;

    return true;
}

bool CMovementComponent::Init(const char* FileName)
{
    if (!CComponent::Init(FileName))
        return false;

    return true;
}

void CMovementComponent::PreUpdate(float DeltaTime)
{
    CComponent::PreUpdate(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else if (mUpdateComponent->IsEnable())
        {
        }
    }
}

void CMovementComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else if (mUpdateComponent->IsEnable())
        {
            mVelocity.Normalize();

            if (mVelocity.Length() > 0.f)
            {
                mMoveStep = mVelocity * mSpeed * DeltaTime;

                mUpdateComponent->AddWorldPos(mMoveStep);
            }
        }
    }
}

void CMovementComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else if (mUpdateComponent->IsEnable())
        {
        }
    }
}

void CMovementComponent::PostRender()
{
    CComponent::PostRender();

    mVelocity = FVector3D::Zero;
}

CMovementComponent* CMovementComponent::Clone()
{
    return new CMovementComponent(*this);
}
