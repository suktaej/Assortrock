#include "Trap.h"

CTrap::CTrap()
{
}

CTrap::~CTrap()
{
}

bool CTrap::Init()
{
    return true;
}

void CTrap::Update()
{
}

void CTrap::Output(char* OutBuffer, int CountX)
{
    int Index = mPos.Y * CountX + mPos.X;
    OutBuffer[Index] = '@';
}
