#include "MovementComponent.h"
#include "SceneComponent.h"
#include "NavAgent.h"

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

void CMovementComponent::SetMovePoint(const FVector2D& Pos)
{
    if (mUpdateComponent)
    {
        FVector2D   WorldPos;
        WorldPos.x = mUpdateComponent->GetWorldPosition().x;
        WorldPos.y = mUpdateComponent->GetWorldPosition().y;

        FindPath(WorldPos, Pos);

        if (!mPathList.empty())
        {
            mTargetDist = WorldPos.Distance(mPathList.front());
        }
    }
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
    }
}

void CMovementComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else
        {
            if (mPathList.empty())
            {
                if (mMoveAxis != EAxis::None)
                {
                    mVelocity = mUpdateComponent->GetAxis(mMoveAxis);

                }

                mVelocity.Normalize();

                if (mVelocity.Length() > 0.f)
                {
                    mMoveStep = mVelocity * mSpeed * DeltaTime;
                }

                mUpdateComponent->AddWorldPos(mMoveStep);
            }

            else
            {
                FVector3D   Target;
                Target.x = mPathList.front().x;
                Target.y = mPathList.front().y;

                FVector3D   Dir = Target - 
                    mUpdateComponent->GetWorldPosition();
                Dir.Normalize();

                mMoveStep = Dir * mSpeed * DeltaTime;

                float   StepLength = mMoveStep.Length();

                if (StepLength >= mTargetDist)
                {
                    FVector2D   _Target = mPathList.front();

                    mPathList.pop_front();

                    if (!mPathList.empty())
                    {
                        mTargetDist = _Target.Distance(mPathList.front());
                    }

                    mUpdateComponent->SetWorldPos(Target);
                }

                else
                {
                    mTargetDist -= StepLength;

                    mUpdateComponent->AddWorldPos(mMoveStep);
                }
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
    }
}

CMovementComponent* CMovementComponent::Clone()
{
    return new CMovementComponent(*this);
}

void CMovementComponent::EndFrame()
{
    CComponent::EndFrame();

    if (mVelocityInit)
        mVelocity = FVector3D::Zero;

    mMoveStep = FVector3D::Zero;
}
