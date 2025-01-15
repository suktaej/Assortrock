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
	//이름을 이용하여 메쉬를 얻어옴
	CMesh* Mesh = FindMesh(Name);
	//메쉬가 이미 있을 경우 중복된 메쉬가 있으므로 생성을 중단
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
	std::unordered_map<std::string, CSharedPtr>::iterator iter = m_MeshMap.find(Name);

	if(iter == m_MeshMap.end())
		return nullptr;

	return (CMesh*)iter->second.Get();
}
