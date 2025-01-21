#pragma once
#include "../GameInfo.h"
#include "Shader.h"

class CShaderManager
{
	DECLARE_SINGLE(CShaderManager)
private:
	std::unordered_map<std::string, CSharedPtr<CShader>> m_ShaderMap;
	std::unordered_map<std::string, CSharedPtr<class CConstantBuffer>> m_CBufferMap;
public:
	bool Init();
	CShader* FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);
public:
	bool CreateConstantBuffer(
		const std::string& Name,
		int Size,
		int Register,
		int ShaderBufferType = EShaderBufferType::Graphic);
	CConstantBuffer* FindCBuffer(const std::string& Name);
	void ReleaseCBuffer(const std::string& Name);
public:
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		CShader* Shader = FindShader(Name);

		if (Shader)				//�̹� ���� �̸��� ���̴��� �����ϸ� ��ȯ
			return true;

		Shader = new T;			//���ٸ� ���ø�Ÿ�� ����

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);
			return false;
		}

		m_ShaderMap.insert(std::make_pair(Name, Shader));

		return true;
	}
};

