#include "AssetManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CAssetManager)
CAssetManager::CAssetManager()
{
}
CAssetManager::~CAssetManager()
{
}

bool CAssetManager::Init()
{
	m_MeshManager = new CMeshManager;
	return true;
}
