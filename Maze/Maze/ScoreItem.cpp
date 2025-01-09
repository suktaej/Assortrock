#include "ScoreItem.h"

FScoreItem::FScoreItem()
{
}

FScoreItem::~FScoreItem()
{
}

bool FScoreItem::Init()
{
	return true;
}

void FScoreItem::Update()
{
}

void FScoreItem::Output(char* Buffer, int CountX)
{
	int Index = mPos.Y * CountX + mPos.X;
	Buffer[Index] = 'I';
}
