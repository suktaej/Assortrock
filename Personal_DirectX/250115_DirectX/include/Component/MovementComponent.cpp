#include "MovementComponent.h"
#include "SceneComponent.h"

CMovementComponent::CMovementComponent()
{
}

CMovementComponent::CMovementComponent(const CMovementComponent& Com)  :
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
        //무브먼트가 활성화 되어 있을 때
        else
        {
            //축 값이 none이 아니라면 velcotiy를 MoveAxis로 설정
            if (mMoveAxis != EAxis::None)
                mVelocity = mUpdateComponent->GetAxis(mMoveAxis);
            
            mVelocity.Normalize();
            //이동해야하는 상황일 때
            if (mVelocity.Length() > 0.f)
                //현재 프레임에 이동해야 하는 스텝 생성
                mMoveStep = mVelocity * mSpeed * DeltaTime;

            mUpdateComponent->AddWorldPos(mMoveStep);
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

void CMovementComponent::PostRender()
{
    CComponent::PostRender();

    if (mVelocityInit)
        mVelocity = FVector3D::Zero;

    mMoveStep = FVector3D::Zero;
}

CMovementComponent* CMovementComponent::Clone()
{
    return new CMovementComponent(*this);
}
