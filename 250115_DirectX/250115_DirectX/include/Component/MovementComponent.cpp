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
        //�����Ʈ�� Ȱ��ȭ �Ǿ� ���� ��
        else
        {
            //�� ���� none�� �ƴ϶�� velcotiy�� MoveAxis�� ����
            if (mMoveAxis != EAxis::None)
                mVelocity = mUpdateComponent->GetAxis(mMoveAxis);
            
            mVelocity.Normalize();
            //�̵��ؾ��ϴ� ��Ȳ�� ��
            if (mVelocity.Length() > 0.f)
                //���� �����ӿ� �̵��ؾ� �ϴ� ���� ����
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
