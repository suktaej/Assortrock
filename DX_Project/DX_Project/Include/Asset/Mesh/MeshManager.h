#pragma once

#include "../../GameInfo.h"

class CMeshManager
{	
	friend class CAssetManager;
private:
	CMeshManager();
	~CMeshManager();

private:
	//생성된 mesh를 저장 및 빠른 탐색을 위한 unordered_map
	std::unordered_map<std::string, CSharedPtr<class CMesh>> mMeshMap;
public:
	bool Init();
	bool CreateMesh(
		const std::string& Name,
		void* VertexData,
		int Size,
		int Count,
		D3D11_USAGE VertexUsage,
		D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr,
		int IndexSize = 0,
		int IndexCount = 0,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);
	void ReleaseMesh(class CAsset* Mesh);
};

