#pragma once
#include "../GameInfo.h"
#include "Shader.h"

class CShaderManager
{
	DECLARE_SINGLE(CShaderManager)
private:
	std::unordered_map<std::string, CSharedPtr<CShader>> m_ShaderMap;

public:
	bool Init();
	CShader* FindShader(const std::string& Name);

	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		CShader* Shader = FindShader(Name);

		if (Shader)
			return true;

		Shader = new T;

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);
			return false;
		}

		m_ShaderMap.insert(std::make_pair(Name, Shader));

		return true;
	}
};

