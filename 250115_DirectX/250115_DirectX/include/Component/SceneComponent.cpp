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

void CSceneComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);
}

void CSceneComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);
}

void CSceneComponent::Collision(float DeltaTime)
{
    CComponent::Collision(DeltaTime);
}

void CSceneComponent::PreRender()
{
    CComponent::PreRender();

    m_MatScale.Scaling(m_WorldScale);

}

void CSceneComponent::Render()
{
    CComponent::Render();
}

void CSceneComponent::PostRender()
{
    CComponent::PostRender();
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
{
    SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{
    SetRelativeScale(FVector3D(Scale.x, Scale.y, 1.f));
}

void CSceneComponent::SetRelativeScale(float x, float y)
{
    SetRelativeScale(FVector3D(x, y, 1.f));
}
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
        //나의 상대위치에 부모의 상대위치를 합
        //위에서 도출한 회전을 적용(회전행렬에 곱)
        m_ChildList[i]->m_WorldPos = m_ChildList[i]->m_RelativePos.GetRotation(m_WorldRot) + m_WorldPos;
    }

}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
    SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeRotation(const FVector2D& Rot)
{
    SetRelativeRotation(FVector3D(Rot.x, Rot.y, 0.f));
}

void CSceneComponent::SetRelativeRotation(float x, float y)
{
    SetRelativeRotation(FVector3D(x, y, 0.f));
}

void CSceneComponent::SetWorldRotationX(float x)
{
    SetRelativeRotation(FVector3D(x, m_RelativeRot.y, m_RelativeRot.z));
}

void CSceneComponent::SetWorldRotationY(float y)
{
    SetRelativeRotation(FVector3D(m_RelativeRot.x, y, m_RelativeRot.z));
}

void CSceneComponent::SetWorldRotationZ(float z)
{
    SetRelativeRotation(FVector3D(m_RelativeRot.x, m_RelativeRot.y, z));
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
}
#pragma endregion Rotation

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
{
    SetWorldScale(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{
    SetWorldScale(FVector3D(Scale.x, Scale.y, m_WorldScale.z));
}

void CSceneComponent::SetWorldScale(float x, float y)
{
    SetWorldScale(FVector3D(x, y, m_WorldScale.z));
}
#pragma endregion WorldScale

void CSceneComponent::SetWorldRotation(const FVector3D& Rot)
{
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
}

void CSceneComponent::SetWorldRotation(const FVector2D& Rot)
{
}

void CSceneComponent::SetWorldRotation(float x, float y)
{
}

void CSceneComponent::SetWorldRotationX(float x)
{
}

void CSceneComponent::SetWorldRotationY(float y)
{
}

void CSceneComponent::SetWorldRotationZ(float z)
{
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
}

void CSceneComponent::SetWorldPos(const FVector3D& Pos)
{
}

void CSceneComponent::SetWorldPos(float x, float y, float z)
{
}

void CSceneComponent::SetWorldPos(const FVector2D& Pos)
{
}

void CSceneComponent::SetWorldPos(float x, float y)
{
}
