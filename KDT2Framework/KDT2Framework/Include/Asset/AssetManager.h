#pragma once

#include "../GameInfo.h"

class CAssetManager
{
private:
	class CMeshManager* mMeshManager = nullptr;
	class CTextureManager* mTextureManager = nullptr;

public:
	class CMeshManager* GetMeshManager()	const
	{
		return mMeshManager;
	}

	class CTextureManager* GetTextureManager()	const
	{
		return mTextureManager;
	}

public:
	bool Init();
	void ReleaseAsset(class CAsset* Asset);

	DECLARE_SINGLE(CAssetManager)
};

