#include "TransformCBuffer.h"

CTransformCBuffer::CTransformCBuffer()
{
}

CTransformCBuffer::CTransformCBuffer(const CTransformCBuffer& Data)
    :CConstantBufferData(Data), m_Data(Data.m_Data)
{
}

CTransformCBuffer::CTransformCBuffer(CTransformCBuffer&& Data)
    :CConstantBufferData(Data), m_Data(Data.m_Data)
{
}

CTransformCBuffer::~CTransformCBuffer()
{
}

bool CTransformCBuffer::Init()
{
    SetConstantBuffer("Transform");
    return true;
}

void CTransformCBuffer::UpdateBuffer()
{
    m_Data.matWV = m_Data.matWorld * m_Data.matView;
    m_Data.matWVP = m_Data.matWV * m_Data.matProj;
    
    //���̴����� �������� ��������� �о�� �� ���η� ����� �о��
    //��ġ��ķ� ����
    m_Data.matWorld.Transpose();
    m_Data.matView.Transpose();
    m_Data.matProj.Transpose();
    m_Data.matWV.Transpose();
    m_Data.matWVP.Transpose();

    m_Buffer->Update(&m_Data);
}

CTransformCBuffer* CTransformCBuffer::Clone()
{
    return new CTransformCBuffer(*this);
}
