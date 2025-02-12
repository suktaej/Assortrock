#pragma once

#include "../GameInfo.h"

class CRenderManager
{
private:
	class CRenderStateManager* mStateManager = nullptr;

public:
	class CRenderStateManager* GetStateManager()
	{
		return mStateManager;
	}

public:
	bool Init();
	void Render();

	DECLARE_SINGLE(CRenderManager)
};

