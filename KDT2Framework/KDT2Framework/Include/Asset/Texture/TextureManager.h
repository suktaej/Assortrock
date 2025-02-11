#pragma once

#include "../../GameInfo.h"

class CTextureManager
{
	friend class CAssetManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CTexture>>	mTextureMap;

public:
	bool Init();

	bool LoadTexture(const std::string& Name,
		const TCHAR* FileName);
	bool LoadTextureFullPath(const std::string& Name,
		const TCHAR* FullPath);

	class CTexture* FindTexture(const std::string& Name);

	void ReleaseTexture(class CAsset* Texture);
};

