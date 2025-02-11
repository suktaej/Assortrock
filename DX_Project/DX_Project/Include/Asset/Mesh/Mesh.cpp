#include "Mesh.h"
#include "../../Device.h"
//#include "../Material/Material.h"
//#include "../Material/MaterialManager.h"
//#include "../../Asset/AssetManager.h"
//#include "../../Scene/Scene.h"
//#include "../../Scene/SceneAssetManager.h"

CMesh::CMesh()
{
	//mAssetType = EAssetType::Mesh;
}

CMesh::~CMesh()
{
	//Slot은 동적할당되어 생성되므로 소멸자 호출 시 제거
	size_t	Size = mMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(mMeshSlot[i]);
	}
}

bool CMesh::CreateMesh(
	void* VertexData,
	int Size,
	int Count,
	D3D11_USAGE VertexUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive,
	void* IndexData,
	int IndexSize,
	int IndexCount,
	DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
/*
struct FVertexBuffer {
	ID3D11Buffer* Buffer = nullptr;
	int	Size = 0;
	int	Count = 0;
	void* Data = nullptr;
*/
	mVertexBuffer.Size = Size;
	mVertexBuffer.Count = Count;
/*
struct FVector3D {
	float	x = 0.f;
	float	y = 0.f;
	float	z = 0.f;
*/
	//정점 정보는 Vector3D struct type
	//크기만큼 동적할당
	mVertexBuffer.Data = new char[Size * Count];
	//할당된 메모리에 데이터를 복사
	memcpy(mVertexBuffer.Data, VertexData, Size * Count);
	
	//입력받은 정보로 버퍼를 생성
	if (!CreateBuffer(
		&mVertexBuffer.Buffer,
		D3D11_BIND_VERTEX_BUFFER,
		VertexData,
		Size,
		Count,
		VertexUsage))
		return false;
	//모양지정
	mPrimitive = Primitive;

	// 인덱스 데이터가 있다면 인덱스버퍼 생성
	if (IndexData)
	{
		//IndexBuffer는 Slot struct에 포함되어 있으므로 Slot 생성
		FMeshSlot* Slot = new FMeshSlot;

		Slot->IndexBuffer.Size = IndexSize;
		Slot->IndexBuffer.Count = IndexCount;
		Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
		Slot->IndexBuffer.Fmt = Fmt;
		memcpy(Slot->IndexBuffer.Data, IndexData, IndexSize * IndexCount);
	
		//Index Buffer 생성
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
		//Slot->Material = CAssetManager::GetInst()->GetMaterialManager()->FindMaterial("DefaultMaterial");

		//슬롯이 생성되었다면 슬롯벡터에 삽입
		mMeshSlot.push_back(Slot);
	}

	return true;
}

bool CMesh::CreateBuffer(
	ID3D11Buffer** Buffer,
	D3D11_BIND_FLAG Flag,
	void* Data,
	int Size,
	int Count,
	D3D11_USAGE Usage)
{
	//DX에서 지원
	//버퍼 생성시 사용되는 구조체
	D3D11_BUFFER_DESC	BufferDesc = {};

	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.Usage = Usage;
	BufferDesc.BindFlags = Flag;

	// Dynamic 일 경우 CPU에서 버퍼 데이터를 바꿀 수 있게 한다.
	if (Usage == D3D11_USAGE_DYNAMIC)
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	else if (Usage == D3D11_USAGE_STAGING)
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	
	// DX 지원
	// 버퍼나 텍스처를 초기화 할 때 사용
	// ID3D11Device::CreateBuffer 또는 
	// ID3D11Device::CreateTexture* 함수에서 초기 데이터를 제공하는 용도
	D3D11_SUBRESOURCE_DATA	BufferData = {};

	BufferData.pSysMem = Data;	//초기화할 데이터의 포인터

	if (FAILED(CDevice::GetInst()->GetDevice()->
		//DX지원
		//실제 버퍼 생성
		CreateBuffer(&BufferDesc, &BufferData, Buffer)))
		return false;

	return true;
}

/*
void CMesh::SetMaterial(int SlotIndex, const std::string& Name)
{
	CMaterial* Material = nullptr;

	if (mScene)
		Material = mScene->GetAssetManager()->FindMaterial(Name);

	else
		Material = CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name);

	mMeshSlot[SlotIndex]->Material = Material;
}

void CMesh::SetMaterial(int SlotIndex, CMaterial* Material)
{
	mMeshSlot[SlotIndex]->Material = Material;
}

void CMesh::Render()
{
	unsigned int Stride = mVertexBuffer.Size;
	unsigned int Offset = 0;

	// 그려줄 도형 타입을 지정한다.
	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(mPrimitive);
	// 버텍스버퍼를 지정한다.
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
		&mVertexBuffer.Buffer, &Stride, &Offset);

	size_t	SlotCount = mMeshSlot.size();

	// 인덱스버퍼가 있을 경우 없을 경우로 나누어서 출력한다.

	if (SlotCount > 0)
	{
		for (size_t i = 0; i < SlotCount; ++i)
		{
			// 출력에 사용할 인덱스버퍼를 지정한다.
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(mMeshSlot[i]->IndexBuffer.Buffer,
				mMeshSlot[i]->IndexBuffer.Fmt, 0);

			// 인덱스를 참고하여 화면에 도형을 그린다.
			CDevice::GetInst()->GetContext()->DrawIndexed(mMeshSlot[i]->IndexBuffer.Count,
				0, 0);
		}
	}

	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr,
			DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInst()->GetContext()->Draw(mVertexBuffer.Count,
			0);
	}
}

void CMesh::Render(int SlotIndex)
{
	unsigned int Stride = mVertexBuffer.Size;
	unsigned int Offset = 0;

	// 그려줄 도형 타입을 지정한다.
	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(mPrimitive);
	// 버텍스버퍼를 지정한다.
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
		&mVertexBuffer.Buffer, &Stride, &Offset);

	size_t	SlotCount = mMeshSlot.size();

	// 인덱스버퍼가 있을 경우 없을 경우로 나누어서 출력한다.

	if (SlotCount > 0)
	{
		// 출력에 사용할 인덱스버퍼를 지정한다.
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(mMeshSlot[SlotIndex]->IndexBuffer.Buffer,
			mMeshSlot[SlotIndex]->IndexBuffer.Fmt, 0);

		// 인덱스를 참고하여 화면에 도형을 그린다.
		CDevice::GetInst()->GetContext()->DrawIndexed(mMeshSlot[SlotIndex]->IndexBuffer.Count,
			0, 0);
	}

	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr,
			DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInst()->GetContext()->Draw(mVertexBuffer.Count,
			0);
	}
}
*/
