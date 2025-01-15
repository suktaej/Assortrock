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
}

bool CMesh::CreateMesh(
	void* VertexData,	//���ؽ� ������ �迭
	int Size,			//���ؽ� �������� ũ��(byte)
	int Count,			//���ؽ� ������ ����
	D3D11_USAGE VertexUsage,	//������ ������
	D3D11_PRIMITIVE_TOPOLOGY Primitive,	//������ �� �⺻����
	void* IndexData,
	int IndexSize,
	int IndexCount,
	DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
	m_VertexBuffer.Size = Size;
	m_VertexBuffer.Count = Count;
	//�迭 ���� 1�� �� 1byte�� �����ϱ� ���� char
	//VertexData�� GPU���� ����� �� �ֵ��� ���� �޸𸮿� ����
	m_VertexBuffer.Data = new char[Size * Count];
	memcpy(m_VertexBuffer.Data, VertexData, Size * Count);
	m_Primitive = Primitive;
	
	//���ؽ� ���� ����
	if (!CreateBuffer(&m_VertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER, VertexData, Size, Count, VertexUsage))
		return false;

	//�ε��� �����Ͱ� ������ ��� �ε��� ���� ����
	if (IndexData)
		//###
	{	
		//���ο� �Ž������� ����
		FMeshSlot* Slot = new FMeshSlot;

		Slot->IndexBuffer.Size = IndexSize;
		Slot->IndexBuffer.Count = IndexCount;
		Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
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
	D3D11_BIND_FLAG Flag,	//������ ������ ����
	void* Data,
	int Size,
	int Count,
	D3D11_USAGE Usage)
{
	//���� ��ũ����
	D3D11_BUFFER_DESC BufferDesc = {};
	
	//������ ����Ʈ���� ����
	//������ ũ��* ����
	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.Usage = Usage;
	BufferDesc.BindFlags = Flag;

	if (Usage == D3D11_USAGE_DYNAMIC)
		//CPU���� ������ ������ �����ϵ��� ����
		BufferDesc.CPUAccessFlags -= D3D11_CPU_ACCESS_WRITE;
	else if(Usage == D3D11_USAGE_STAGING)
		//CPU���� read, write ��� �����ϵ��� ����
		BufferDesc.CPUAccessFlags -= D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	//���۸� ����
	D3D11_SUBRESOURCE_DATA BufferData = {};
	BufferData.pSysMem = Data;

	if(FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&BufferDesc,&BufferData,Buffer)))
		return false;

	return true;

}
