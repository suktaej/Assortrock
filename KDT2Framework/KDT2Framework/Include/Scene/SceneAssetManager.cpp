#include "SceneAssetManager.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Asset/Material/Material.h"
#include "../Asset/Material/MaterialManager.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Animation/Animation2DManager.h"
#include "../Asset/Sound/Sound.h"
#include "../Asset/Sound/SoundManager.h"

CSceneAssetManager::CSceneAssetManager()
{
}

CSceneAssetManager::~CSceneAssetManager()
{
	auto	iter = mAssetMap.begin();

	for (; iter != mAssetMap.end();)
	{
		CAsset* Asset = iter->second;

		iter = mAssetMap.erase(iter);

		CAssetManager::GetInst()->ReleaseAsset(Asset);
	}
}

bool CSceneAssetManager::Init()
{
	return true;
}

bool CSceneAssetManager::CreateMesh(
	const std::string& Name, void* VertexData, 
	int Size, int Count, D3D11_USAGE VertexUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData,
	int IndexSize, int IndexCount, DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
	if (!CAssetManager::GetInst()->GetMeshManager()->CreateMesh(
		Name, VertexData, Size, Count, VertexUsage,
		Primitive, IndexData, IndexSize, IndexCount,
		Fmt, IndexUsage))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter != mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name)));
	}

	return true;
}

CMesh* CSceneAssetManager::FindMesh(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CMesh* Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);

		if (!Mesh)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Mesh));
		
		return Mesh;
	}

	return dynamic_cast<CMesh*>(iter->second.Get());
}

bool CSceneAssetManager::LoadTexture(
	const std::string& Name, const TCHAR* FileName)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadTextureFullPath(
	const std::string& Name, const TCHAR* FullPath)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTextureFullPath(
		Name, FullPath))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadTexture(
	const std::string& Name, 
	const std::vector<const TCHAR*>& FileName)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadTextureFullPath(
	const std::string& Name, 
	const std::vector<const TCHAR*>& FullPath)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTextureFullPath(
		Name, FullPath))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadTexture(
	const std::string& Name, const TCHAR* FileName, 
	const TCHAR* Ext, int Count)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName, Ext, Count))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

CTexture* CSceneAssetManager::FindTexture(
	const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CTexture* Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);

		if (!Texture)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Texture));

		return Texture;
	}

	return dynamic_cast<CTexture*>(iter->second.Get());
}

bool CSceneAssetManager::CreateMaterial(
	const std::string& Name)
{
	if (!CAssetManager::GetInst()->GetMaterialManager()->CreateMaterial(
		Name))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name)));
	}

	return true;
}

CMaterial* CSceneAssetManager::FindMaterial(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CMaterial* Material = CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name);

		if (!Material)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Material));

		return Material;
	}

	return dynamic_cast<CMaterial*>(iter->second.Get());
}

bool CSceneAssetManager::CreateAnimation(
	const std::string& Name)
{
	if (!CAssetManager::GetInst()->GetAnimationManager()->CreateAnimation(
		Name))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(Name)));
	}

	return true;
}

bool CSceneAssetManager::SetAnimationTextureType(
	const std::string& Name, EAnimationTextureType Type)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetAnimationTextureType(Type);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(const std::string& Name,
	CTexture* Texture)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(Texture);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(const std::string& Name,
	const std::string& TextureName, const TCHAR* FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(
	const std::string& Name, 
	const std::string& TextureName, 
	std::vector<const TCHAR*> FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(
	const std::string& Name, 
	const std::string& TextureName, 
	const TCHAR* FileName, const TCHAR* Ext, int Count)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(TextureName, FileName, Ext,
		Count);

	return true;
}

bool CSceneAssetManager::SetAnimationTextureFullPath(
	const std::string& Name, 
	const std::string& TextureName,
	const TCHAR* FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

bool CSceneAssetManager::SetAnimationTextureFullPath(
	const std::string& Name,
	const std::string& TextureName, 
	std::vector<const TCHAR*> FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

bool CSceneAssetManager::AddAnimationFrame(
	const std::string& Name, const FVector2D& Start, 
	const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrame(Start, Size);

	return true;
}

bool CSceneAssetManager::AddAnimationFrame(
	const std::string& Name, float StartX, float StartY,
	float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrame(StartX, StartY, SizeX, SizeY);

	return true;
}

bool CSceneAssetManager::AddAnimationFrameCount(
	const std::string& Name, int Count, 
	const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrameCount(Count, Start, Size);

	return true;
}

bool CSceneAssetManager::AddAnimationFrameCount(
	const std::string& Name, int Count, float StartX,
	float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrameCount(Count, StartX, StartY,
		SizeX, SizeY);

	return true;
}

CAnimation2DData* CSceneAssetManager::FindAnimation(
	const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CAnimation2DData* Animation = 
			CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(Name);

		if (!Animation)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Animation));

		return Animation;
	}

	return dynamic_cast<CAnimation2DData*>(iter->second.Get());
}

bool CSceneAssetManager::LoadSound(const std::string& Name, 
	const std::string& GroupName, bool Loop, const char* FileName)
{
	if (!CAssetManager::GetInst()->GetSoundManager()->LoadSound(
		Name, GroupName, Loop, FileName))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetSoundManager()->FindSound(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadSoundFullPath(const std::string& Name,
	const std::string& GroupName, bool Loop, const char* FullPath)
{
	if (!CAssetManager::GetInst()->GetSoundManager()->LoadSoundFullPath(
		Name, GroupName, Loop, FullPath))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetSoundManager()->FindSound(Name)));
	}

	return true;
}

CSound* CSceneAssetManager::FindSound(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CSound* Sound =
			CAssetManager::GetInst()->GetSoundManager()->FindSound(Name);

		if (!Sound)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Sound));

		return Sound;
	}

	return dynamic_cast<CSound*>(iter->second.Get());
}
