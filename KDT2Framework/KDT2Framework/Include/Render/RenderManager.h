#pragma once

#include "../GameInfo.h"

class CRenderManager
{
private:
	class CRenderStateManager* mStateManager = nullptr;
	std::list<CSharedPtr<class CSceneComponent>>	mRenderList;
	ERenderSortType	mRenderSortType = ERenderSortType::Y;
	ID3D11SamplerState* mSampler = nullptr;

public:
	class CRenderStateManager* GetStateManager()
	{
		return mStateManager;
	}

	void SetSortType(ERenderSortType Type)
	{
		mRenderSortType = Type;
	}

	void AddRenderList(class CSceneComponent* Component);
	void ClearRenderList();

public:
	bool Init();
	void Render();

private:
	static bool SortY(const CSharedPtr<class CSceneComponent>& Src,
		const CSharedPtr<class CSceneComponent>& Dest);

	static bool SortAlpha(const CSharedPtr<class CSceneComponent>& Src,
		const CSharedPtr<class CSceneComponent>& Dest);

	DECLARE_SINGLE(CRenderManager)
};

