#include "SceneComponent.h"

CSceneComponent::CSceneComponent()
{
}

CSceneComponent::CSceneComponent(const CSceneComponent& Com) :
    CComponent(Com)
{
}

CSceneComponent::CSceneComponent(CSceneComponent&& Com) :
    CComponent(Com)
{
}

CSceneComponent::~CSceneComponent()
{
    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        mChildList[i]->Destroy();
    }
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
    Child->mParent = this;

    mChildList.emplace_back(Child);

    Child->ComputeTransform();
}

bool CSceneComponent::Init()
{
    return true;
}

bool CSceneComponent::Init(const char* FileName)
{
    return true;
}

void CSceneComponent::PreUpdate(float DeltaTime)
{
    CComponent::PreUpdate(DeltaTime);

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->PreUpdate(DeltaTime);
        ++iter;
    }
}

void CSceneComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Update(DeltaTime);
        ++iter;
    }
}

void CSceneComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->PostUpdate(DeltaTime);
        ++iter;
    }
}

void CSceneComponent::Collision(float DeltaTime)
{
    CComponent::Collision(DeltaTime);

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Collision(DeltaTime);
        ++iter;
    }
}

void CSceneComponent::PreRender()
{
    CComponent::PreRender();

    mmatScale.Scaling(mWorldScale);
    mmatRot.Rotation(mWorldRot);
    mmatTranslate.Translation(mWorldPos);

    mmatWorld = mmatScale * mmatRot * mmatTranslate;

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->PreRender();
        ++iter;
    }
}

void CSceneComponent::Render()
{
    CComponent::Render();

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Render();
        ++iter;
    }
}

void CSceneComponent::PostRender()
{
    CComponent::PostRender();

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());

            mChildList.pop_back();
            iterEnd = mChildList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->PostRender();
        ++iter;
    }
}

CSceneComponent* CSceneComponent::Clone()
{
    return new CSceneComponent(*this);
}

void CSceneComponent::SetRelativeScale(const FVector3D& Scale)
{
    mRelativeScale = Scale;

    if (mParent)
    {
        mWorldScale = mRelativeScale * mParent->mWorldScale;
    }

    else
    {
        mWorldScale = mRelativeScale;
    }

    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        mChildList[i]->mWorldPos = mChildList[i]->mRelativePos * mWorldScale +
            mWorldPos;

        mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
    }
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
    SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{
    SetRelativeScale(FVector3D(Scale.x, Scale.y, mRelativeScale.z));
}

void CSceneComponent::SetRelativeScale(float x, float y)
{
    SetRelativeScale(FVector3D(x, y, mRelativeScale.z));
}

void CSceneComponent::SetRelativeRotation(const FVector3D& Rot)
{
    mRelativeRot = Rot;

    if (mParent)
    {
        mWorldRot = mRelativeRot + mParent->mWorldRot;
    }

    else
    {
        mWorldRot = mRelativeRot;
    }

    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        /*mChildList[i]->mWorldPos =
            mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos;*/
        FVector3D   ParentRot = GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
        // 회전하는 행렬을 만들어준다.
        memcpy(&matRot._41, &mWorldPos, sizeof(FVector3D));

        mChildList[i]->mWorldPos = mChildList[i]->mRelativePos.TransformCoord(matRot);

        mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);
    }
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
    SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeRotation(const FVector2D& Rot)
{
    SetRelativeRotation(FVector3D(Rot.x, Rot.y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotation(float x, float y)
{
    SetRelativeRotation(FVector3D(x, y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationX(float x)
{
    SetRelativeRotation(FVector3D(x, mRelativeRot.y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationY(float y)
{
    SetRelativeRotation(FVector3D(mRelativeRot.x, y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationZ(float z)
{
    SetRelativeRotation(FVector3D(mRelativeRot.x, mRelativeRot.y, z));
}

void CSceneComponent::SetRelativeRotationAxis(float Angle, const FVector3D& Axis)
{
}

void CSceneComponent::SetRelativePos(const FVector3D& Pos)
{
    mRelativePos = Pos;

    if (mParent)
    {
        mWorldPos = mRelativePos + mParent->mWorldPos;
    }

    else
    {
        mWorldPos = mRelativePos;
    }

    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
    }
}

void CSceneComponent::SetRelativePos(float x, float y, float z)
{
    SetRelativePos(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativePos(const FVector2D& Pos)
{
    SetRelativePos(FVector3D(Pos.x, Pos.y, mRelativePos.z));
}

void CSceneComponent::SetRelativePos(float x, float y)
{
    SetRelativePos(FVector3D(x, y, mRelativePos.z));
}

void CSceneComponent::SetWorldScale(const FVector3D& Scale)
{
    mWorldScale = Scale;

    if (mParent)
    {
        mRelativeScale = mWorldScale / mParent->mWorldScale;
    }

    else
    {
        mRelativeScale = mWorldScale;
    }

    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);

        mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos * mWorldScale + mWorldPos);
    }
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
    SetWorldScale(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{
    SetWorldScale(FVector3D(Scale.x, Scale.y, mWorldScale.z));
}

void CSceneComponent::SetWorldScale(float x, float y)
{
    SetWorldScale(FVector3D(x, y, mWorldScale.z));
}

void CSceneComponent::SetWorldRotation(const FVector3D& Rot)
{
    mWorldRot = Rot;

    if (mParent)
    {
        mRelativeRot = mWorldRot - mParent->mWorldRot;
    }

    else
    {
        mRelativeRot = mWorldRot;
    }

    FVector3D   Axis[EAxis::End] =
    {
        FVector3D(1.f, 0.f, 0.f),
        FVector3D(0.f, 1.f, 0.f),
        FVector3D(0.f, 0.f, 1.f)
    };

    FMatrix matRot;
    matRot.Rotation(mWorldRot);

    // 회전된 축을 구한다.
    mAxis[EAxis::X] = Axis[EAxis::X].TransformNormal(matRot);
    mAxis[EAxis::Y] = Axis[EAxis::Y].TransformNormal(matRot);
    mAxis[EAxis::Z] = Axis[EAxis::Z].TransformNormal(matRot);

    mAxis[EAxis::X].Normalize();
    mAxis[EAxis::Y].Normalize();
    mAxis[EAxis::Z].Normalize();

    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);

        FVector3D   ParentRot = GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
        // 회전하는 행렬을 만들어준다.
        memcpy(&matRot._41, &mWorldPos, sizeof(FVector3D));

        mChildList[i]->mWorldPos = mChildList[i]->mRelativePos.TransformCoord(matRot);
        /*mChildList[i]->SetWorldPos(
            mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos);*/
    }
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
    SetWorldRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldRotation(const FVector2D& Rot)
{
    SetWorldRotation(FVector3D(Rot.x, Rot.y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotation(float x, float y)
{
    SetWorldRotation(FVector3D(x, y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationX(float x)
{
    SetWorldRotation(FVector3D(x, mWorldRot.y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationY(float y)
{
    SetWorldRotation(FVector3D(mWorldRot.x, y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationZ(float z)
{
    SetWorldRotation(FVector3D(mWorldRot.x, mWorldRot.y, z));
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
}

void CSceneComponent::SetWorldPos(const FVector3D& Pos)
{
    mWorldPos = Pos;

    if (mParent)
    {
        FVector3D   ParentRot = mParent->GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
        // 회전하는 행렬을 만들어준다.
        memcpy(&matRot._41, &mParent->mWorldPos, sizeof(FVector3D));

        mWorldPos = mRelativePos.TransformCoord(matRot);

        /*FVector3D RelativePos = mWorldPos - mParent->mWorldPos;
        mRelativePos = RelativePos.GetRotation(mParent->mWorldRot * -1.f);*/
    }

    else
    {
        mRelativePos = mWorldPos;
    }

    size_t  Size = mChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
    }
}

void CSceneComponent::SetWorldPos(float x, float y, float z)
{
    SetWorldPos(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldPos(const FVector2D& Pos)
{
    SetRelativeRotation(FVector3D(Pos.x, Pos.y, mRelativePos.z));
}

void CSceneComponent::SetWorldPos(float x, float y)
{
    SetRelativeRotation(FVector3D(x, y, mRelativePos.z));
}

void CSceneComponent::ComputeTransform()
{
    SetWorldScale(mRelativeScale * mParent->mWorldScale);
    SetWorldRotation(mRelativeRot + mParent->mWorldRot);
    SetWorldPos(mRelativePos + mParent->mWorldPos);
}
