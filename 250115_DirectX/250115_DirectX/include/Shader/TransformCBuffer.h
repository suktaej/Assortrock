#pragma once
#include "ConstantBufferData.h"

class CTransformCBuffer :
    public CConstantBufferData
{
public:
	CTransformCBuffer();
	CTransformCBuffer(const CTransformCBuffer& Data);
	CTransformCBuffer(CTransformCBuffer&& Data);
	~CTransformCBuffer() override;

private:
	FTransformCBufferInfo	m_Data;

public:
	bool Init() override;
	void UpdateBuffer() override;
	//��Ӱ����� Ŭ������ �ڽ�Ŭ���� Ÿ������ �����ؼ� ������ ����
	CTransformCBuffer* Clone() override;

public:
	void SetWorldMatrix(const FMatrix& matWorld) { m_Data.matWorld = matWorld; }
	void SetViewMatrix(const FMatrix& matView) { m_Data.matView = matView; }
	void SetProjMatrix(const FMatrix& matProj) { m_Data.matProj = matProj; }
};

