#include "MeshManager.h"
#include "StaticMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::CreateMesh(const std::string& Name,void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
	//�̸��� �̿��Ͽ� �޽��� ����
	CMesh* Mesh = FindMesh(Name);
	//�޽��� �̹� ���� ��� �ߺ��� �޽��� �����Ƿ� ������ �ߴ�
	if (Mesh)
		return true;

	Mesh = new CStaticMesh;

	if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage, Primitive, IndexData, IndexSize, IndexCount, Fmt, IndexUsage))
	{
		SAFE_DELETE(Mesh);
		return false;
	}

	m_MeshMap.insert(std::make_pair(Name, Mesh));

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPtr<CMesh>>::iterator iter = m_MeshMap.find(Name);

	if(iter == m_MeshMap.end())
		return nullptr;

	return (CMesh*)iter->second.Get();
}

bool CMeshManager::Init()
{
	FVertexColor BoxVtx[8] =
	{
		FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),
		FVertexColor(0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f),
		FVertexColor(-0.5f, -0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, 1.f),

		FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 1.f, 1.f),
		FVertexColor(0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f),
		FVertexColor(-0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),
	};

	unsigned short  BoxIdx[36] =
	{
		0, 1, 3, 0, 3, 2,
		1, 5, 7, 1, 7, 3,
		5, 4, 6, 5, 6, 7,
		4, 0, 2, 4, 2, 6,
		4, 5, 1, 4, 1, 0,
		2, 3, 7, 2, 7, 6
	};

	if (!CreateMesh("Box", BoxVtx, sizeof(FVertexColor), 8, D3D11_USAGE_DEFAULT,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, BoxIdx, sizeof(unsigned short), 36, DXGI_FORMAT_R16_UINT))
		return false;

	FVertexColor    CenterRect[4] =
	{
		FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),
		FVertexColor(0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f),
		FVertexColor(-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 1.f),
	};

	unsigned short RectIdx[6] = { 0, 1, 3, 0, 3, 2 };

	if (!CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 4, D3D11_USAGE_DEFAULT,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIdx, sizeof(unsigned short), 6, DXGI_FORMAT_R16G16B16A16_UINT))
		return false;

	return true;
}