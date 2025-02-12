#pragma once

#include "../GameInfo.h"

class CRenderStateManager
{
	friend class CRenderManager;

private:
	CRenderStateManager();
	~CRenderStateManager();

private:
	std::unordered_map<std::string, class CRenderState*> mRenderStateMap;

public:
	bool Init();

public:
	void SetBlendFactor(const std::string& Name, 
		float r, float g, float b, float a);
	void SetSampleMask(const std::string& Name, UINT Mask);
	void AddBlendDesc(const std::string& Name,
		bool Enable, D3D11_BLEND Src,
		D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
		D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha,
		D3D11_BLEND_OP AlphaOp,
		UINT8 RenderTargetWriteMask);
	bool CreateBlendState(const std::string& Name,
		bool AlphaToCoverageEnable,
		bool IndependentBlendEnable);

public:
	class CRenderState* FindState(const std::string& Name);
};

