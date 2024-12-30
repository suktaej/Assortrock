#include "Item.h"
#include "Stage.h"

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

void CItem::Update(float Time)
{
}

void CItem::Output(char* Buffer)
{
    int Xsize = CStage::GetInst()->GetXsize();

    Buffer[mPos.Y * (Xsize + 1) + mPos.X] = 'I';
}
