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
	//서브 리소스 데이터는 필요시 값을 생성 후 쉐이더로 전달
	//버텍스버퍼나 인덱스버퍼는 미리 값을 저장
	//트랜스폼 상수버퍼의 행렬 수 만큼 별도의 클래스(ConstantBufferData)가 필요
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_Buffer)))
		return false;

	return true;
}

void CConstantBuffer::Update(void* Data)
{
	//Buffer안에 있는 데이터를 저장하기 위한 배열의 주소를 가져옴
	D3D11_MAPPED_SUBRESOURCE Map = {};

	CDevice::GetInst()->GetContext()->Map(
		m_Buffer,
		0,							//UINT type 
		D3D11_MAP_WRITE_DISCARD,	//D311_MAP, 기존 데이터를 삭제 후 갱신
		0,
		&Map);
	
	memcpy(Map.pData, Data, m_Size);	//버퍼의 주소, 인자, 크기
	
	//위에서 인자로 들어온 데이터를 버퍼로 넘겨주면
	//지정된 Shader에 상수버퍼의 데이터를 넘겨준다
	CDevice::GetInst()->GetContext()->Unmap(m_Buffer, 0);

	//& 비트연산으로 true일 경우 실행
	//렌더링 최적화시 상수버퍼를 모두 벡터에 전달 후 한번에 전달하는 것이 빠름
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
