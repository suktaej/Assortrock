#include "Mesh.h"
#include "../../Device.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	size_t Size = m_MeshSlot.size();

	for (size_t i = 0;i < Size;i++)
		SAFE_DELETE(m_MeshSlot[i]);

	m_MeshSlot.clear();
}

bool CMesh::CreateMesh(
	void* VertexData,	//버텍스 데이터 배열
	int Size,			//버텍스 데이터의 크기(byte)
	int Count,			//버텍스 데이터 개수
	D3D11_USAGE VertexUsage,	//버퍼의 저장방식
	D3D11_PRIMITIVE_TOPOLOGY Primitive,	//렌더링 시 기본도형
	void* IndexData,
	int IndexSize,
	int IndexCount,
	DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
	m_VertexBuffer.Size = Size;
	m_VertexBuffer.Count = Count;
	//배열 개수 1개 당 1byte로 생성하기 위한 char
	//VertexData를 GPU에서 사용할 수 있도록 동적 메모리에 복사
	m_VertexBuffer.Data = new char[Size * Count];
	memcpy(m_VertexBuffer.Data, VertexData, Size * Count);
	m_Primitive = Primitive;
	
	//버텍스 버퍼 생성
	if (!CreateBuffer(&m_VertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER, VertexData, Size, Count, VertexUsage))
		return false;

	//인덱스 데이터가 존재할 경우 인덱스 버퍼 생성
	if (IndexData)
	{	
		//새로운 매쉬슬롯을 생성
		FMeshSlot* Slot = new FMeshSlot;

		Slot->IndexBuffer.Size = IndexSize;
		Slot->IndexBuffer.Count = IndexCount;
		Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
		Slot->IndexBuffer.Fmt = Fmt;
		memcpy(Slot->IndexBuffer.Data, IndexData, IndexSize * IndexCount);

		if (!CreateBuffer(
			&Slot->IndexBuffer.Buffer,
			D3D11_BIND_INDEX_BUFFER,
			IndexData,
			IndexSize,
			IndexCount,
			IndexUsage))
		{
			SAFE_DELETE(Slot);
			return false;
		}
		m_MeshSlot.push_back(Slot);
	}
	return true;
}

bool CMesh::CreateBuffer(
	ID3D11Buffer** Buffer,
	D3D11_BIND_FLAG Flag,	//생성할 버퍼의 형식
	void* Data,
	int Size,
	int Count,
	D3D11_USAGE Usage)
{
	//버퍼 디스크립션
	D3D11_BUFFER_DESC BufferDesc = {};
	
	//버퍼의 바이트수를 지정
	//버퍼의 크기* 개수
	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.Usage = Usage;
	BufferDesc.BindFlags = Flag;

	if (Usage == D3D11_USAGE_DYNAMIC)
		//CPU에서 버퍼의 갱신이 가능하도록 구현
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	else if(Usage == D3D11_USAGE_STAGING)
		//CPU에서 read, write 사용 가능하도록 구현
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	//버퍼를 생성
	D3D11_SUBRESOURCE_DATA BufferData = {};
	BufferData.pSysMem = Data;

	if(FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&BufferDesc,&BufferData,Buffer)))
		return false;

	return true;
}

void CMesh::Render()
{
	//stride: 정점 하나의 크기
	//offset: 
	unsigned int Stride = m_VertexBuffer.Size;
	unsigned int Offset = 0;

	// 그려줄 도형 타입을 지정한다.
	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_Primitive);
	// 버텍스버퍼를 지정한다.
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(
		0,
		1,
		&m_VertexBuffer.Buffer,
		&Stride,
		&Offset);

	size_t	SlotCount = m_MeshSlot.size();
	// 인덱스버퍼가 있을 경우 없을 경우로 나누어서 출력한다.

	if (SlotCount > 0)
	{
		for (size_t i = 0; i < SlotCount; ++i)
		{
			// 출력에 사용할 인덱스버퍼를 지정한다.
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				m_MeshSlot[i]->IndexBuffer.Buffer,
				m_MeshSlot[i]->IndexBuffer.Fmt,
				0);
			// 인덱스를 참고하여 화면에 도형을 그린다.
			CDevice::GetInst()->GetContext()->DrawIndexed(
				m_MeshSlot[i]->IndexBuffer.Count,
				0, 
				0);
		}
	}
	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			nullptr, 
			DXGI_FORMAT_UNKNOWN, 
			0);
		CDevice::GetInst()->GetContext()->Draw(
			m_VertexBuffer.Count, 
			0);
	}
}
