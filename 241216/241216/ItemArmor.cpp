#include "ItemArmor.h"

CItemArmor::CItemArmor()//    :
    //mType(EItemType::Armor)
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

    std::cout << "종류 : 방어구" << std::endl;
    std::cout << "방어력 : " << mOption << std::endl;

    CItem::Output();
}

CItemArmor* CItemArmor::Clone()
{
    // 
    return new CItemArmor(*this);
}
