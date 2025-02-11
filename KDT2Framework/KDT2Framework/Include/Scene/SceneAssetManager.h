#pragma once

#include "../GameInfo.h"

class CSceneAssetManager
{
	friend class CScene;

private:
	CSceneAssetManager();
	~CSceneAssetManager();

private:
	class CScene* mScene = nullptr;

private:
	std::unordered_map<std::string, CSharedPtr<class CAsset>>	mAssetMap;

public:
	bool Init();

#pragma region Mesh

public:
	bool CreateMesh(const std::string& Name, void* VertexData, int Size, int Count,
		D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);

#pragma endregion Mesh


#pragma region Texture

public:
	bool LoadTexture(const std::string& Name,
		const TCHAR* FileName);
	bool LoadTextureFullPath(const std::string& Name,
		const TCHAR* FullPath);

	class CTexture* FindTexture(const std::string& Name);

#pragma endregion Texture

#pragma region Material

	bool CreateMaterial(const std::string& Name);

	class CMaterial* FindMaterial(const std::string& Name);

#pragma endregion Material
};

