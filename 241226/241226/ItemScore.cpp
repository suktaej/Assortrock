#include "ItemScore.h"
#include "StageManager.h"

CItemScore::CItemScore()
{
	mCollisionType = ECollisionType::Score;
}

CItemScore::~CItemScore()
{
}

bool CItemScore::Init()
{
	return true;
}

void CItemScore::Output(char* OutputBuffer)
{
	int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
	OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = 's';
}
