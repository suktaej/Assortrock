#pragma once
#include "ConstantBuffer.h"

class CConstantBufferData abstract
{
public:
	CConstantBufferData();
	CConstantBufferData(const CConstantBufferData& Data);
	CConstantBufferData(CConstantBufferData&& Data);
	virtual ~CConstantBufferData();
protected:
	CSharedPtr<CConstantBufferData> m_Buffer;
};

