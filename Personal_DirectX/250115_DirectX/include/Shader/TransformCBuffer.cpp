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
    
    //쉐이더에서 레지스터 행렬정보를 읽어올 때 세로로 행렬을 읽어옴
    //전치행렬로 연산
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
