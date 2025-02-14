#include "RenderManager.h"
#include "RenderStateManager.h"
#include "RenderState.h"
#include "../Component/SceneComponent.h"
#include "../Device.h"

DEFINITION_SINGLE(CRenderManager)

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
	SAFE_RELEASE(mSampler);
	SAFE_DELETE(mStateManager);
}

void CRenderManager::AddRenderList(CSceneComponent* Component)
{
	mRenderList.emplace_back(Component);
}

void CRenderManager::ClearRenderList()
{
	mRenderList.clear();
}

bool CRenderManager::Init()
{
	mStateManager = new CRenderStateManager;

	mStateManager->Init();

	D3D11_SAMPLER_DESC	Desc = {};

	Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	Desc.MipLODBias = 0.f;
	Desc.MaxAnisotropy = 1;
	Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	Desc.MinLOD = -FLT_MAX;
	Desc.MaxLOD = FLT_MAX;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateSamplerState(
		&Desc, &mSampler)))
		return false;

	return true;
}

void CRenderManager::Render()
{
	switch (mRenderSortType)
	{
	case ERenderSortType::None:
		break;
	case ERenderSortType::Y:
		if (mRenderList.size() > 1)
			mRenderList.sort(CRenderManager::SortY);
		break;
	case ERenderSortType::Alpha:
		if (mRenderList.size() > 1)
			mRenderList.sort(CRenderManager::SortAlpha);
		break;
	}

	CDevice::GetInst()->GetContext()->PSSetSamplers(0,
		1, &mSampler);

	auto	iter = mRenderList.begin();
	auto	iterEnd = mRenderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mRenderList.erase(iter);
			iterEnd = mRenderList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreRender();

		(*iter)->Render();

		(*iter)->PostRender();

		++iter;
	}
}

bool CRenderManager::SortY(
	const CSharedPtr<class CSceneComponent>& Src, 
	const CSharedPtr<class CSceneComponent>& Dest)
{
	float SrcY = Src->GetWorldPosition().y -
		Src->GetWorldScale().y * Src->GetPivot().y;

	float DestY = Dest->GetWorldPosition().y -
		Dest->GetWorldScale().y * Dest->GetPivot().y;

	return SrcY < DestY;
}

bool CRenderManager::SortAlpha(
	const CSharedPtr<class CSceneComponent>& Src, 
	const CSharedPtr<class CSceneComponent>& Dest)
{
	return false;
}
