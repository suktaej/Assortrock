#include "ShaderManager.h"
#include "ColorMeshShader.h"
#include "FrameMeshShader.h"
#include "ConstantBuffer.h"

DEFINITION_SINGLE(CShaderManager)

CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
}

bool CShaderManager::Init()
{
	CreateShader<CColorMeshShader>("ColorMeshShader");

	CreateShader<CFrameMeshShader>("FrameMeshShader");



	CreateConstantBuffer("Transform",
		sizeof(FTransformCBufferInfo),
		0, EShaderBufferType::Vertex);

	CreateConstantBuffer("Collider",
		sizeof(FColliderCBufferInfo),
		1, EShaderBufferType::Pixel);

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	//std::unordered_map<std::string, CSharedPtr>::iterator
	auto iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	auto iter = mShaderMap.find(Name);

	if (iter != mShaderMap.end())
	{
		mShaderMap.erase(iter);
	}
}

bool CShaderManager::CreateConstantBuffer(
	const std::string& Name, int Size, 
	int Register, int ShaderBufferType)
{
	CConstantBuffer* CBuffer = FindCBuffer(Name);

	if (CBuffer)
		return true;

	CBuffer = new CConstantBuffer;

	if (!CBuffer->Init(Size, Register, ShaderBufferType))
	{
		SAFE_DELETE(CBuffer);
		return false;
	}

	mCBufferMap.insert(std::make_pair(Name, CBuffer));

	return true;
}

CConstantBuffer* CShaderManager::FindCBuffer(
	const std::string& Name)
{
	auto iter = mCBufferMap.find(Name);

	if (iter == mCBufferMap.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseCBuffer(const std::string& Name)
{
	auto iter = mCBufferMap.find(Name);

	if (iter != mCBufferMap.end())
	{
		mCBufferMap.erase(iter);
	}
}
