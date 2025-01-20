#include "ConstantBuffer.h"
#include "../Device.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
}

bool CConstantBuffer::Init(int Size, int Register, int ShaderBufferType)
{
	m_Size = Size;
	m_Register = 0;
	//m_ShadeBufferType = ShaderBufferType;

	D3D11_BUFFER_DESC Desc = {};
	
	//������۴� ���������� ���� ������ Dynamic���� ����
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	//���� ũ��
	Desc.ByteWidth = Size;
	//������ͷ� ���ε�
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPU���� ������� ���� ���ڴٰ� ����
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc), nullptr, &m_Buffer))
		return;

	return false;
}
