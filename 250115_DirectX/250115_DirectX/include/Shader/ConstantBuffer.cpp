#include "ConstantBuffer.h"
#include "../Device.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
	SAFE_RELEASE(m_Buffer);
}

bool CConstantBuffer::Init(int Size, int Register, int ShaderBufferType)
{
	m_Size = Size;
	m_Register = 0;
	m_ShaderBufferType = ShaderBufferType;

	D3D11_BUFFER_DESC Desc = {};
	
	//������۴� ���������� ���� ������ Dynamic���� ����
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	//���� ũ��
	Desc.ByteWidth = Size;
	//������ͷ� ���ε�
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPU���� ������� ���� ���ڴٰ� ����
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//���� ���ҽ� �����ʹ� �ʿ�� ���� ���� �� ���̴��� ����
	//���ؽ����۳� �ε������۴� �̸� ���� ����
	//Ʈ������ ��������� ��� �� ��ŭ ������ Ŭ����(ConstantBufferData)�� �ʿ�
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_Buffer)))
		return false;

	return true;
}

void CConstantBuffer::Update(void* Data)
{
	//Buffer�ȿ� �ִ� �����͸� �����ϱ� ���� �迭�� �ּҸ� ������
	D3D11_MAPPED_SUBRESOURCE Map = {};

	CDevice::GetInst()->GetContext()->Map(
		m_Buffer,
		0,							//UINT type 
		D3D11_MAP_WRITE_DISCARD,	//D311_MAP, ���� �����͸� ���� �� ����
		0,
		&Map);
	
	memcpy(Map.pData, Data, m_Size);	//������ �ּ�, ����, ũ��
	
	//������ ���ڷ� ���� �����͸� ���۷� �Ѱ��ָ�
	//������ Shader�� ��������� �����͸� �Ѱ��ش�
	CDevice::GetInst()->GetContext()->Unmap(m_Buffer, 0);

	//& ��Ʈ�������� true�� ��� ����
	//������ ����ȭ�� ������۸� ��� ���Ϳ� ���� �� �ѹ��� �����ϴ� ���� ����
	if (m_ShaderBufferType & EShaderBufferType::Vertex)
		CDevice::GetInst()->GetContext()->VSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & EShaderBufferType::Pixel)
		CDevice::GetInst()->GetContext()->PSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & EShaderBufferType::Hull)
		CDevice::GetInst()->GetContext()->HSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & EShaderBufferType::Domain)
		CDevice::GetInst()->GetContext()->DSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & EShaderBufferType::Geometry)
		CDevice::GetInst()->GetContext()->GSSetConstantBuffers(m_Register, 1, &m_Buffer);

	if (m_ShaderBufferType & EShaderBufferType::Compute)
		CDevice::GetInst()->GetContext()->CSSetConstantBuffers(m_Register, 1, &m_Buffer);
}
