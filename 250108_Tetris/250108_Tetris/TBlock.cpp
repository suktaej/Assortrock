#include "TBlock.h"
#include "StageManager.h"
#include "Stage.h"

FTBlock::FTBlock()
{
}

FTBlock::~FTBlock()
{
}

bool FTBlock::Init()
{
	return true;
}

void FTBlock::Output(char* Buffer)
{
	int Xsize = FStageManager::GetInst()->GetStage()->GetXsize();
	Buffer[mPos.Y * (Xsize + 1) + mPos.X] = 'T';
}
