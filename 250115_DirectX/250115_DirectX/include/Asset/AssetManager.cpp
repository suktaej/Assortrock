#include "AssetManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CAssetManager)

CAssetManager::CAssetManager()
{
}
CAssetManager::~CAssetManager()
{
	SAFE_DELETE(m_MeshManager);
}

bool CAssetManager::Init()
{
	m_MeshManager = new CMeshManager;
	if (!m_MeshManager->Init())
		return false;

	return true;
}
