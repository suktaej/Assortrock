#include "StageManager.h"
#include "Stage.h"

FStageManager* FStageManager::s_Inst = nullptr;

FStageManager::FStageManager()
{
}

FStageManager::~FStageManager()
{
}
bool FStageManager::Init()
{
	return true;
}

void FStageManager::Run()
{
	m_Stage = new FStage;
	m_Stage->Init();
	m_Stage->Run();

	SAFE_DELETE(m_Stage);
}

