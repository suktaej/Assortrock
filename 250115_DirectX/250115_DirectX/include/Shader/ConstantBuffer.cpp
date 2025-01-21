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
	
	//상수버퍼는 정보갱신이 많기 때문에 Dynamic으로 지정
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	//버퍼 크기
	Desc.ByteWidth = Size;
	//상수버터로 바인딩
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPU에서 상수버퍼 값을 쓰겠다고 정의
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//서브리소스 데이터는 필요시 값을 생성 후 쉐이더로 전달
	//버텍스버퍼나 인덱스버퍼는 미리 값을 저장
	//트랜스폼 상수버퍼의 행렬 수 만큼 별도의 클래스(ConstantBufferData)가 필요
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_Buffer)))
		return false;

	return true;
}
