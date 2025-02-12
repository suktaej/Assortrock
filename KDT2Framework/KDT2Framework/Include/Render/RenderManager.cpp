#include "RenderManager.h"
#include "RenderStateManager.h"
#include "RenderState.h"

DEFINITION_SINGLE(CRenderManager)

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
	SAFE_DELETE(mStateManager);
}

bool CRenderManager::Init()
{
	mStateManager = new CRenderStateManager;

	mStateManager->Init();

	return true;
}

void CRenderManager::Render()
{
}
