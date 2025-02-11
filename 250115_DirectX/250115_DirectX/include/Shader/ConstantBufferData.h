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
	//�������� ������ ���� �� ������ ����� ������ �ʿ�
	//��ü�� ����ϱ� �� ���۸� ����
	//�����͸� ������ ����
	//���۴� Ʈ������ ������� �ϳ��� �ʿ�
	//�� ���۸� �����ؼ� ���
	//������ ���۸� ������ �߻� Ȯ���� ���⿡ sharedptr�� ���� ��ȭ
	CSharedPtr<CConstantBuffer> m_Buffer;
protected:
	void SetConstantBuffer(const std::string& Name);
public:
	virtual bool Init() = 0;
	virtual void UpdateBuffer() = 0;
	virtual CConstantBufferData* Clone() = 0;
};

