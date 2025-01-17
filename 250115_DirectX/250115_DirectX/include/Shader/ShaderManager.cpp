#include "ShaderManager.h"
#include "ColorMeshShader.h"

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
	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	//	std::unordered_map<std::string, CSharedPtr<CShader>>::iterator
	auto iter = m_ShaderMap.find(Name);
	//TODO: type check
	if (iter == m_ShaderMap.end())
	{
		return nullptr;
	}

	return (CShader*)iter->second.Get();
}
