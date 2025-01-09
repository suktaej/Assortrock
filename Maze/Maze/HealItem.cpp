#include "HealItem.h"

FHealItem::FHealItem()
{
}

FHealItem::~FHealItem()
{
}

bool FHealItem::Init()
{
    return true;
}

void FHealItem::Update()
{
}

void FHealItem::Output(char* Buffer, int CountX)
{
    int Index = mPos.Y * CountX + mPos.X;
    Buffer[Index] = 'H';
}
