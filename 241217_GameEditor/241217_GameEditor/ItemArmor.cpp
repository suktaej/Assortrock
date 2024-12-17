#include "ItemArmor.h"

CItemArmor::CItemArmor()
{
    mType = EItemType::Armor;
}

CItemArmor::CItemArmor(const CItemArmor& Obj)   :
    CItem(Obj)
{
}

CItemArmor::~CItemArmor()
{
}

bool CItemArmor::Init()
{
    CItem::Init();
    return true;
}

bool CItemArmor::Init(FILE* File)
{
    CItem::Init(File);

    return true;
}

void CItemArmor::Output()
{
    CObject::Output();
    std::cout << "Type: Armor" << std::endl;
    std::cout << "Defense:" << mOption << std::endl;
    CItem::Output();
}

CItemArmor* CItemArmor::Clone()
{
    return new CItemArmor(*this);
}
