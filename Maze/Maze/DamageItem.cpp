#include "DamageItem.h"

FDamageItem::FDamageItem()
{
}

FDamageItem::~FDamageItem()
{
}

bool FDamageItem::Init()
{
    return true;
}

void FDamageItem::Update()
{
}

void FDamageItem::Output(char* Buffer, int CountX)
{
    int Index = mPos.Y * CountX + mPos.X;
    Buffer[Index] = 'D';
}
