#include "Item.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

bool CItem::Init()
{
    return true;
}

void CItem::Update()
{
}

void CItem::Output(char* OutBuffer,int CountX)
{
    int Index = mPos.Y * CountX + mPos.X;
    OutBuffer[Index] = '*';
}
