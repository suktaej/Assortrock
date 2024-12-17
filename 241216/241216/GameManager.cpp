#include "GameManager.h"
#include "ObjectManager.h"
#include "BattleManager.h"

DEFINITION_SINGLE(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CObjectManager::DestroyInst();

	CBattleManager::DestroyInst();
}

bool CGameManager::Init()
{
	CObjectManager::GetInst()->Init();

	CBattleManager::GetInst()->Init();

	return true;
}

void CGameManager::Run()
{
	CBattleManager::GetInst()->Run();
}
