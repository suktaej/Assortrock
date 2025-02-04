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
    std::vector<CSharedPtr<CSceneComponent>>::iterator iter = m_ChildList.begin();
    std::vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = m_ChildList.end();

    while (iter != iterEnd)
    {
        if (!(*iter)->IsActive())
        {
            //������ �� ���� ������ ���� ��ü
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
            //������ �� ���� ������ ���� ��ü
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
            //������ �� ���� ������ ���� ��ü
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
            // ������ �� ���� ������ ���� �ٲ۴�.
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
    //���� ���
    m_MatWorld = m_MatScale * m_MatRot * m_MatTranslate;

    std::vector<CSharedPtr<CSceneComponent>>::iterator  iter;
    std::vector<CSharedPtr<CSceneComponent>>::iterator  iterEnd = m_ChildList.end();

    for (iter = m_ChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // ������ �� ���� ������ ���� �ٲ۴�.
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
            // ������ �� ���� ������ ���� �ٲ۴�.
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
            // ������ �� ���� ������ ���� �ٲ۴�.
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

    //�θ� ���� ��� �ڽ��� ���� �������� �θ��� ���彺���Ͽ� �ڽ��� ���彺������ ��
    if (m_Parent)
        m_WorldScale = m_RelativeScale * m_Parent->m_WorldScale;
    //���� ��� �ڽ��� �������� ���彺����
    else
        m_WorldScale = m_RelativeScale;

    //��������ȭ�� �ڽĵ��� ����
    //�ڽ� �� ��ŭ �ݺ�
    size_t Size = m_ChildList.size();

    for (size_t i = 0;i < Size;i++)
    {
		//�θ��� ũ�Ⱑ ���ϸ� �� ������ŭ �ڽ��� ��ġ���� ����
		//���� �����ġ�� �θ�κ��� �󸶳� ������ �ִ����� ��Ÿ���� �� 
		//���� �����ġ���� ������ ���� �� �θ��� �����ġ�� ���ϸ� ������ �������� �̵��� ��ġ���� ����
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

        // ����� 41, 42, 43 �� �θ��� ��ġ�� �־� �θ��� ��ġ�� �߽�����
        // ȸ���ϴ� ����� ������ش�.
        memcpy(&matRot._41, &m_WorldPos, sizeof(FVector3D));

        //���� �����ġ�� �θ��� �����ġ�� ��
        //������ ������ ȸ���� ����(ȸ����Ŀ� ��)
        m_ChildList[i]->m_WorldPos = m_ChildList[i]->m_RelativePos.GetRotation(m_WorldRot) + m_WorldPos;
        //child�� ���ȸ�� ������ ����
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

    if (m_Parent)
    {
        FVector3D ParentRot = m_Parent->GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        memcpy(&matRot._41, &m_WorldPos, sizeof(FVector3D));

        m_WorldPos = m_RelativePos.TransformCoord(matRot);
    }
    else
        m_WorldPos = m_RelativePos;
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

    // ȸ���� ���� ���Ѵ�.
    mAxis[(int)EAxis::X] = Axis[(int)EAxis::X].TransformNormal(matRot);
    mAxis[(int)EAxis::Y] = Axis[(int)EAxis::Y].TransformNormal(matRot);
    mAxis[(int)EAxis::Z] = Axis[(int)EAxis::Z].TransformNormal(matRot);
    
    //Normalize
    mAxis[(int)EAxis::X].Normalize();
    mAxis[(int)EAxis::Y].Normalize();
    mAxis[(int)EAxis::Z].Normalize();

    size_t  Size = m_ChildList.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_ChildList[i]->SetWorldRotation(m_ChildList[i]->m_RelativeRot + m_WorldRot);

        FVector3D   ParentRot = GetWorldRotation();

        FMatrix matRot;
        matRot.Rotation(ParentRot);

        // ����� 41, 42, 43 �� �θ��� ��ġ�� �־� �θ��� ��ġ�� �߽�����
        // ȸ���ϴ� ����� ������ش�.
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

        // ����� 41, 42, 43 �� �θ��� ��ġ�� �־� �θ��� ��ġ�� �߽�����
        // ȸ���ϴ� ����� ������ش�.
        // �޸𸮿� ���ӵ� �ּҷ� ���ԵǾ� ����
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
{ SetWorldPos(FVector3D(Pos.x, Pos.y, m_WorldPos.z)); }
 void CSceneComponent::SetWorldPos(float x, float y)
{ SetWorldPos(FVector3D(x, y, m_WorldPos.z)); }
#pragma endregion WorldPos

#pragma region AddFunc
 void CSceneComponent::AddRelativeScale(const FVector3D& Scale)
 {
     m_RelativeScale += Scale;

     SetRelativeScale(m_RelativeScale);
 }

 void CSceneComponent::AddRelativeScale(float x, float y, float z)
 {
     AddRelativeScale(FVector3D(x, y, z));
 }

 void CSceneComponent::AddRelativeScale(const FVector2D& Scale)
 {
     AddRelativeScale(FVector3D(Scale.x, Scale.y, 0.f));
 }

 void CSceneComponent::AddRelativeScale(float x, float y)
 {
     AddRelativeScale(FVector3D(x, y, 0.f));
 }

 void CSceneComponent::AddRelativeRotation(const FVector3D& Rot)
 {
     m_RelativeRot += Rot;

     SetRelativeRotation(m_RelativeRot);
 }

 void CSceneComponent::AddRelativeRotation(float x, float y, float z)
 {
     AddRelativeRotation(FVector3D(x, y, z));
 }

 void CSceneComponent::AddRelativeRotation(const FVector2D& Rot)
 {
     AddRelativeRotation(FVector3D(Rot.x, Rot.y, 0.f));
 }

 void CSceneComponent::AddRelativeRotation(float x, float y)
 {
     AddRelativeRotation(FVector3D(x, y, 0.f));
 }

 void CSceneComponent::AddRelativeRotationX(float x)
 {
     AddRelativeRotation(FVector3D(x, 0.f, 0.f));
 }

 void CSceneComponent::AddRelativeRotationY(float y)
 {
     AddRelativeRotation(FVector3D(0.f, y, 0.f));
 }

 void CSceneComponent::AddRelativeRotationZ(float z)
 {
     AddRelativeRotation(FVector3D(0.f, 0.f, z));
 }

 void CSceneComponent::AddRelativePos(const FVector3D& Pos)
 {
     m_RelativePos += Pos;

     SetRelativePos(m_RelativePos);
 }

 void CSceneComponent::AddRelativePos(float x, float y, float z)
 {
     AddRelativePos(FVector3D(x, y, z));
 }

 void CSceneComponent::AddRelativePos(const FVector2D& Pos)
 {
     AddRelativePos(FVector3D(Pos.x, Pos.y, 0.f));
 }

 void CSceneComponent::AddRelativePos(float x, float y)
 {
     AddRelativePos(FVector3D(x, y, 0.f));
 }

 void CSceneComponent::AddWorldScale(const FVector3D& Scale)
 {
     m_WorldScale += Scale;

     SetWorldScale(m_WorldScale);
 }

 void CSceneComponent::AddWorldScale(float x, float y, float z)
 {
     AddWorldScale(FVector3D(x, y, z));
 }

 void CSceneComponent::AddWorldScale(const FVector2D& Scale)
 {
     AddWorldScale(FVector3D(Scale.x, Scale.y, 0.f));
 }

 void CSceneComponent::AddWorldScale(float x, float y)
 {
     AddWorldScale(FVector3D(x, y, 0.f));
 }

 void CSceneComponent::AddWorldRotation(const FVector3D& Rot)
 {
     m_WorldRot += Rot;

     SetWorldRotation(m_WorldRot);
 }

 void CSceneComponent::AddWorldRotation(float x, float y, float z)
 {
     AddWorldRotation(FVector3D(x, y, z));
 }

 void CSceneComponent::AddWorldRotation(const FVector2D& Rot)
 {
     AddWorldRotation(FVector3D(Rot.x, Rot.y, 0.f));
 }

 void CSceneComponent::AddWorldRotation(float x, float y)
 {
     AddWorldRotation(FVector3D(x, y, 0.f));
 }

 void CSceneComponent::AddWorldRotationX(float x)
 {
     AddWorldRotation(FVector3D(x, 0.f, 0.f));
 }

 void CSceneComponent::AddWorldRotationY(float y)
 {
     AddWorldRotation(FVector3D(0.f, y, 0.f));
 }

 void CSceneComponent::AddWorldRotationZ(float z)
 {
     AddWorldRotation(FVector3D(0.f, 0.f, z));
 }

 void CSceneComponent::AddWorldPos(const FVector3D& Pos)
 {
     m_WorldPos += Pos;

     SetWorldPos(m_WorldPos);
 }

 void CSceneComponent::AddWorldPos(float x, float y, float z)
 {
     AddWorldPos(FVector3D(x, y, z));
 }

 void CSceneComponent::AddWorldPos(const FVector2D& Pos)
 {
     AddWorldPos(FVector3D(Pos.x, Pos.y, 0.f));
 }

 void CSceneComponent::AddWorldPos(float x, float y)
 {
     AddWorldPos(FVector3D(x, y, 0.f));
 }
#pragma endregion AddFunc
 void CSceneComponent::ComputeTransform()
{
    SetWorldScale(m_RelativeScale * m_Parent->m_WorldScale);
    SetWorldRotation(m_RelativeRot + m_Parent->m_WorldRot);
    SetWorldPos(m_RelativePos + m_Parent->m_WorldPos);
}
