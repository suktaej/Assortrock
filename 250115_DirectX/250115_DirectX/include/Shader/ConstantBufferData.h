#pragma once
#include "ConstantBuffer.h"
#include "ShaderManager.h"
class CConstantBufferData abstract
{
public:
	CConstantBufferData();
	CConstantBufferData(const CConstantBufferData& Data);
	CConstantBufferData(CConstantBufferData&& Data);
	virtual ~CConstantBufferData();
protected:
	//여러개의 데이터 보유 시 각각의 행렬이 별도로 필요
	//물체를 출력하기 전 버퍼만 전달
	//데이터만 별도로 보유
	//버퍼는 트랜스폼 상수버퍼 하나만 필요
	//이 버퍼를 공유해서 사용
	//공유로 뎅글링 포인터 발생 확률이 높기에 sharedptr을 통해 완화
	CSharedPtr<CConstantBuffer> m_Buffer;
protected:
	void SetConstantBuffer(const std::string& Name);
public:
	virtual bool Init() = 0;
	virtual void UpdateBuffer() = 0;
	virtual CConstantBufferData* Clone() = 0;
};

