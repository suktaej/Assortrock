#pragma once

#include "ConstantBufferData.h"

class CTransformCBuffer :
    public CConstantBufferData
{
public:
	CTransformCBuffer();
	CTransformCBuffer(const CTransformCBuffer& Data);
	CTransformCBuffer(CTransformCBuffer&& Data);
	virtual ~CTransformCBuffer();

private:
	FTransformCBufferInfo	mData;

public:
	virtual bool Init();
	virtual void UpdateBuffer();
	virtual CTransformCBuffer* Clone();

public:
	void SetWorldMatrix(const FMatrix& matWorld) { mData.matWorld = matWorld; }
	void SetViewMatrix(const FMatrix& matView) { mData.matView = matView; }
	void SetProjMatrix(const FMatrix& matProj) { mData.matProj = matProj; }
	void SetPivot(const FVector3D& Pivot) { mData.Pivot = Pivot; }
};

