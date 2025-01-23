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
    size_t Size = m_ChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        m_ChildList[i]->Destroy();
    }
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
	Child->m_Parent = this;
	m_ChildList.emplace_back(Child);
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
    std::vector<CSharedPtr<CSceneComponent>>::iterator iter = m_ChildList.begin();
    std::vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = m_ChildList.end();

    while (iter != iterEnd)
    {
        if (!(*iter)->IsActive())
        {
            //지워야 할 값과 마지막 값을 교체
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;
            continue;
        }
        (*iter)->PreUpdate(DeltaTime);
        iter++;
    }
}

void CSceneComponent::Update(float DeltaTime) 
{
    CComponent::Update(DeltaTime);
    std::vector<CSharedPtr<CSceneComponent>>::iterator iter = m_ChildList.begin();
    std::vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = m_ChildList.end();

    while (iter != iterEnd)
    {
        if (!(*iter)->IsActive())
        {
            //지워야 할 값과 마지막 값을 교체
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;
            continue;
        }
        (*iter)->Update(DeltaTime);
        iter++;
    }
}
void CSceneComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);
    std::vector<CSharedPtr<CSceneComponent>>::iterator iter = m_ChildList.begin();
    std::vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = m_ChildList.end();

    while (iter != iterEnd)
    {
        if (!(*iter)->IsActive())
        {
            //지워야 할 값과 마지막 값을 교체
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;
            continue;
        }
        (*iter)->PostUpdate(DeltaTime);
        iter++;
    }
}

void CSceneComponent::Collision(float DeltaTime)
{
    CComponent::Collision(DeltaTime);

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = m_ChildList.end();

    for (iter = m_ChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
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

    m_MatScale.Scaling(m_WorldScale);
    m_MatRot.Rotation(m_WorldRot);
    m_MatTranslate.Translation(m_WorldPos);
    //월드 행렬
    m_MatWorld = m_MatScale * m_MatRot * m_MatTranslate;

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = m_ChildList.end();

    for (iter = m_ChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
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
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = m_ChildList.end();

    for (iter = m_ChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
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
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = m_ChildList.end();

    for (iter = m_ChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, m_ChildList.back());

            m_ChildList.pop_back();
            iterEnd = m_ChildList.end();
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

#pragma region Scale 
void CSceneComponent::SetRelativeScale(const FVector3D& Scale)
{
    m_RelativeScale = Scale;

    //부모가 있을 경우 자신의 월드 스케일은 부모의 월드스케일에 자신의 월드스케일을 곱
    if (m_Parent)
        m_WorldScale = m_RelativeScale * m_Parent->m_WorldScale;
    //없을 경우 자신의 스케일이 월드스케일
    else
        m_WorldScale = m_RelativeScale;

    //계층구조화로 자식들이 존재
    //자식 수 만큼 반복
    size_t Size = m_ChildList.size();

    for (size_t i = 0;i < Size;i++)
    {
		//부모의 크기가 변하면 그 비율만큼 자신의 위치값도 변경
		//나의 상대위치는 부모로부터 얼마나 떨어져 있는지를 나타내는 값 
		//나의 상대위치에서 비율을 곱한 후 부모의 상대위치를 더하면 스케일 변경으로 이동된 위치값이 갱신
        m_ChildList[i]->m_WorldPos = m_ChildList[i]->m_RelativePos * m_WorldScale + m_WorldPos;
        m_ChildList[i]->SetWorldScale(m_ChildList[i]->m_RelativeScale * m_WorldScale);
    }
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{ SetRelativeScale(FVector3D(x, y, z)); } 
void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{ SetRelativeScale(FVector3D(Scale.x, Scale.y, 1.f)); } 
void CSceneComponent::SetRelativeScale(float x, float y)
{ SetRelativeScale(FVector3D(x, y, 1.f)); }
#pragma endregion Scale 

#pragma region Rotation
void CSceneComponent::SetRelativeRotation(const FVector3D& Rot)
{
    m_RelativeRot = Rot;

    if (m_Parent)
        m_WorldRot = m_RelativeRot + m_Parent->m_WorldRot;
    else
        m_WorldRot = m_RelativeRot;
  
    size_t Size = m_ChildList.size();

    for (size_t i = 0;i < Size;i++)
    {
        /*mChildList[i]->mWorldPos =
            mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos;*/
        FVector3D   ParentRot = GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
        // 회전하는 행렬을 만들어준다.
        memcpy(&matRot._41, &m_WorldPos, sizeof(FVector3D));

        //나의 상대위치에 부모의 상대위치를 합
        //위에서 도출한 회전을 적용(회전행렬에 곱)
        m_ChildList[i]->m_WorldPos = m_ChildList[i]->m_RelativePos.GetRotation(m_WorldRot) + m_WorldPos;
        //child에 상대회전 정보를 더함
        m_ChildList[i]->SetWorldRotation(m_ChildList[i]->m_RelativeRot + m_WorldRot);
    }
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{ SetRelativeRotation(FVector3D(x, y, z)); } 
void CSceneComponent::SetRelativeRotation(const FVector2D& Rot)
{ SetRelativeRotation(FVector3D(Rot.x, Rot.y, 0.f)); } 
void CSceneComponent::SetRelativeRotation(float x, float y)
{ SetRelativeRotation(FVector3D(x, y, 0.f)); } 
void CSceneComponent::SetRelativeRotationX(float x)
{ SetRelativeRotation(FVector3D(x, m_RelativeRot.y, m_RelativeRot.z)); }
 void CSceneComponent::SetRelativeRotationY(float y)
{ SetRelativeRotation(FVector3D(m_RelativeRot.x, y, m_RelativeRot.z)); }
 void CSceneComponent::SetRelativeRotationZ(float z)
{ SetRelativeRotation(FVector3D(m_RelativeRot.x, m_RelativeRot.y, z)); }
 void CSceneComponent::SetRelativeRotationAxis(float Angle, const FVector3D& Axis)
{ } 
#pragma endregion Rotation

#pragma region Position
void CSceneComponent::SetRelativePos(const FVector3D& Pos)
{
    m_RelativePos = Pos;
}

void CSceneComponent::SetRelativePos(float x, float y, float z)
{
    m_RelativePos.x = x;
    m_RelativePos.y = y;
    m_RelativePos.z = z;
}

void CSceneComponent::SetRelativePos(const FVector2D& Pos)
{
    m_RelativePos.x = Pos.x;
    m_RelativePos.y = Pos.y;
}

void CSceneComponent::SetRelativePos(float x, float y)
{
    m_RelativePos.x = x;
    m_RelativePos.y = y;
}
#pragma endregion Position

#pragma region WorldScale
void CSceneComponent::SetWorldScale(const FVector3D& Scale)
{
    m_WorldScale = Scale;
    
    if (m_Parent)
        m_RelativeScale = m_WorldScale / m_Parent->m_WorldScale;
    else
        m_RelativeScale = m_WorldScale;

    size_t Size = m_ChildList.size();

    for (size_t i = 0;i < Size;i++)
    {
        m_ChildList[i]->m_WorldPos = m_ChildList[i]->m_RelativePos * m_WorldScale + m_WorldPos;
        m_ChildList[i]->SetWorldPos(m_ChildList[i]->m_RelativePos * m_WorldScale + m_WorldPos);
    }
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{ SetWorldScale(FVector3D(x, y, z)); }
void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{ SetWorldScale(FVector3D(Scale.x, Scale.y, m_WorldScale.z)); }
void CSceneComponent::SetWorldScale(float x, float y)
{ SetWorldScale(FVector3D(x, y, m_WorldScale.z)); }
#pragma endregion WorldScale

#pragma region WorldRot
void CSceneComponent::SetWorldRotation(const FVector3D& Rot)
{
    m_WorldRot = Rot;

    if (m_Parent)
        m_RelativeRot = m_WorldRot - m_Parent->m_WorldRot;
    else
        m_RelativeRot = m_WorldRot;

    FVector3D   Axis[(int)EAxis::End] =
    {
        FVector3D(1.f, 0.f, 0.f),
        FVector3D(0.f, 1.f, 0.f),
        FVector3D(0.f, 0.f, 1.f)
    };

    FMatrix matRot;
    matRot.Rotation(m_WorldRot);

    // 회전된 축을 구한다.
    mAxis[(int)EAxis::X] = Axis[(int)EAxis::X].TransformNormal(matRot);
    mAxis[(int)EAxis::Y] = Axis[(int)EAxis::Y].TransformNormal(matRot);
    mAxis[(int)EAxis::Z] = Axis[(int)EAxis::Z].TransformNormal(matRot);

    size_t  Size = m_ChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_ChildList[i]->SetWorldRotation(m_ChildList[i]->m_RelativeRot + m_WorldRot);

        FVector3D   ParentRot = GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
        // 회전하는 행렬을 만들어준다.
        memcpy(&matRot._41, &m_WorldPos, sizeof(FVector3D));

        m_ChildList[i]->m_WorldPos = m_ChildList[i]->m_RelativePos.TransformCoord(matRot);
        /*m_ChildList[i]->SetWorldPos(
            m_ChildList[i]->m_RelativePos.GetRotation(m_WorldRot) + m_WorldPos);*/
    }
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{ SetWorldRotation(FVector3D(x, y, z)); }
void CSceneComponent::SetWorldRotation(const FVector2D& Rot)
{ SetWorldRotation(FVector3D(Rot.x, Rot.y, m_WorldRot.z)); }
void CSceneComponent::SetWorldRotation(float x, float y)
{ SetWorldRotation(FVector3D(x, y, m_WorldRot.z)); }
void CSceneComponent::SetWorldRotationX(float x)
{ SetWorldRotation(FVector3D(x, m_WorldRot.y, m_WorldRot.z)); }
void CSceneComponent::SetWorldRotationY(float y)
{ SetWorldRotation(FVector3D(m_WorldRot.x, y, m_WorldRot.z)); }
void CSceneComponent::SetWorldRotationZ(float z)
{ SetWorldRotation(FVector3D(m_WorldRot.x, m_WorldRot.y, z)); }
void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{ }
#pragma endregion WorldRot

#pragma region WorldPos
void CSceneComponent::SetWorldPos(const FVector3D& Pos)
{
    m_WorldPos = Pos;

    if (m_Parent)
    {
        FVector3D   ParentRot = m_Parent->GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
        // 회전하는 행렬을 만들어준다.
        memcpy(&matRot._41, &m_Parent->m_WorldPos, sizeof(FVector3D));

        m_WorldPos = m_RelativePos.TransformCoord(matRot);

        /*FVector3D RelativePos = m_WorldPos - m_Parent->m_WorldPos;
        m_RelativePos = RelativePos.GetRotation(m_Parent->m_WorldRot * -1.f);*/
    }

    else
        m_RelativePos = m_WorldPos;

    size_t  Size = m_ChildList.size();

    for (size_t i = 0; i < Size; ++i)
        m_ChildList[i]->SetWorldPos(m_ChildList[i]->m_RelativePos + m_WorldPos);
}

void CSceneComponent::SetWorldPos(float x, float y, float z) 
{ SetWorldPos(FVector3D(x, y, z)); }
void CSceneComponent::SetWorldPos(const FVector2D& Pos)
{ SetRelativeRotation(FVector3D(Pos.x, Pos.y, m_RelativePos.z)); }
 void CSceneComponent::SetWorldPos(float x, float y)
{ SetRelativeRotation(FVector3D(x, y, m_RelativePos.z)); }
#pragma endregion WorldPos

 void CSceneComponent::ComputeTransform()
{
    SetWorldScale(m_RelativeScale * m_Parent->m_WorldScale);
    SetWorldRotation(m_RelativeRot + m_Parent->m_WorldRot);
    SetWorldPos(m_RelativePos + m_Parent->m_WorldPos);
}
