#include "ItemWeapon.h"

CItemWeapon::CItemWeapon()
{
    mType = EItemType::Weapon;
}

CItemWeapon::CItemWeapon(const CItemWeapon& Obj)    :
    CItem(Obj)
{

}

CItemWeapon::~CItemWeapon()
{
}

bool CItemWeapon::Init()
{
    CItem::Init();
    return true;
}

bool CItemWeapon::Init(FILE* File)
{
    CItem::Init(File);

    return true;
}

void CItemWeapon::Output()
{
    CObject::Output();
    std::cout << "Type:Weapon" << std::endl;
    std::cout << "Attack: " << mOption << std::endl;
    CItem::Output();
}

CItemWeapon* CItemWeapon::Clone()
{
    return new CItemWeapon(*this);
}
