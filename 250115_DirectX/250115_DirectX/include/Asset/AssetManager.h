#pragma once
#include "../GameInfo.h"

class CAssetManager
{
	DECLARE_SINGLE(CAssetManager)
private:
	class CMeshManager* m_MeshManager = nullptr;
public:
	class CMeshManager* GetMeshManager() const { return m_MeshManager; }
public:
	bool Init();
};

