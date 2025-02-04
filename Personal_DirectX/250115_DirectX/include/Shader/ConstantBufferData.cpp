#include "ConstantBufferData.h"

CConstantBufferData::CConstantBufferData()
{
}

CConstantBufferData::CConstantBufferData(const CConstantBufferData& Data)
{
	m_Buffer = Data.m_Buffer;

}

CConstantBufferData::CConstantBufferData(CConstantBufferData&& Data)
{
	m_Buffer = Data.m_Buffer;

}

CConstantBufferData::~CConstantBufferData()
{
}

void CConstantBufferData::SetConstantBuffer(const std::string& Name)
{
	m_Buffer = CShaderManager::GetInst()->FindCBuffer(Name);
}
