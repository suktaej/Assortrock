#include "GameManager.h"
#include "ObjectManager.h"
#include "Stage.h"

DEFINITION_SINGLE(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CStage::DestroyInst();
	CObjectManager::DestroyInst();
}

bool CGameManager::Init()
{
	if (!CStage::GetInst()->Init())
		return false;
	if (!CObjectManager::GetInst()->Init())
		return false;

	return true;
}

void CGameManager::Run()
{
	mStage = new CStage;
	mStage->Init();
	mStage->Run();
}
