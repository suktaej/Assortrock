#include "IBlock.h"
#include "StageManager.h"
#include "Stage.h"

FIBlock::FIBlock()
{
}

FIBlock::~FIBlock()
{
}

bool FIBlock::Init()
{
	return true;
}

void FIBlock::Output(char* Buffer)
{
	int Xsize = FStageManager::GetInst()->GetStage()->GetXsize();
	Buffer[mPos.Y * (Xsize + 1) + mPos.X] = 'I';
}
