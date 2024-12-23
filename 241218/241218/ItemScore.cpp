#include "ItemScore.h"

CItemScore::CItemScore()
{
}

CItemScore::~CItemScore()
{
}

bool CItemScore::Init()
{
    return true;
}

void CItemScore::Update()
{
}

void CItemScore::Output(char* OutBuffer, int CountX)
{
    int Index = mPos.Y * CountX + mPos.X;
    OutBuffer[Index] = '*';
}
