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
	CreateConstantBuffer(
		"Transform",
		sizeof(FTransformCBufferInfo),
		0,	
		EShaderBufferType::Vertex);

#ifdef _DEBUG
	CreateShader<CColorMeshShader>("FrameMeshShader");
#endif //_DEBUG

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	//std::unordered_map<std::string, CSharedPtr<CShader>>::iterator
	auto iter = m_ShaderMap.find(Name);
	//TODO: type check
	//auto에서 타입을 발견하지 못할경우 end 반환	
	if (iter == m_ShaderMap.end())
		return nullptr;

	return (CShader*)iter->second.Get();
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	auto iter = m_ShaderMap.find(Name);

	if (iter != m_ShaderMap.end())
		m_ShaderMap.erase(iter);
}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, int ShaderBufferType)
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

	m_CBufferMap.insert(std::make_pair(Name, CBuffer));

	return true;
}

CConstantBuffer* CShaderManager::FindCBuffer(const std::string& Name)
{
	auto iter = m_CBufferMap.find(Name);

	if (iter == m_CBufferMap.end())
		return nullptr;

	return iter->second;
}

void CShaderManager::ReleaseCBuffer(const std::string& Name)
{
	auto iter = m_CBufferMap.find(Name);

	if (iter != m_CBufferMap.end())
		m_CBufferMap.erase(iter);
}
