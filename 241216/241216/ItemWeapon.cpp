#include "ItemWeapon.h"

CItemWeapon::CItemWeapon()
{
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
    std::cout << "종류 : 무기" << std::endl;
    std::cout << "공격력 : " << mOption << std::endl;

    CItem::Output();
}

CItemWeapon* CItemWeapon::Clone()
{
    return new CItemWeapon(*this);
}
