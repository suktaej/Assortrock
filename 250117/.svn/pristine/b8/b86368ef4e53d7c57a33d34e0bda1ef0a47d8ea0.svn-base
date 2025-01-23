#include "AssetManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CAssetManager)

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mMeshManager);
}

bool CAssetManager::Init()
{
	mMeshManager = new CMeshManager;

	if (!mMeshManager->Init())
		return false;

	return true;
}
