#include "AssetManager.h"
#include "Mesh/MeshManager.h"
//#include "Texture/TextureManager.h"
//#include "Material/MaterialManager.h"
#include "Asset.h"

DEFINITION_SINGLE(CAssetManager)

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
	//SAFE_DELETE(mMaterialManager);
	//SAFE_DELETE(mTextureManager);
	SAFE_DELETE(mMeshManager);
}

bool CAssetManager::Init()
{
	/*
	// Root���� ��� ����
	// �Ʒ� �Լ��� �������� �̸����� ������ ��ü��θ�
	// ���´�.
	GetModuleFileName(0, gRootPath, MAX_PATH);

	// D:\Lecture\KDT20242\KDT2Framework\KDT2Framework\Bin\KDT2Framework.exe
	int	Length = lstrlen(gRootPath);

	for (int i = Length - 1; i >= 0; --i)
	{
		if (gRootPath[i] == '/' || gRootPath[i] == '\\')
		{
			memset(&gRootPath[i + 1], 0,
				sizeof(TCHAR) * (Length - (i + 1)));
			break;
		}
	}

	mMaterialManager = new CMaterialManager;

	if (!mMaterialManager->Init())
		return false;

	mTextureManager = new CTextureManager;

	if (!mTextureManager->Init())
		return false;
*/
	mMeshManager = new CMeshManager;

	if (!mMeshManager->Init())
		return false;

	return true;
}

/*
void CAssetManager::ReleaseAsset(CAsset* Asset)
{
	switch (Asset->GetAssetType())
	{
	case EAssetType::Mesh:
		mMeshManager->ReleaseMesh(Asset);
		break;
	case EAssetType::Texture:
		mTextureManager->ReleaseTexture(Asset);
		break;
	}
}
*/
