#include "Character.h"

CCharacter::CCharacter()
{
    mObjType = EObjectType::Character;
}

CCharacter::CCharacter(const CCharacter& Obj):CObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
    return true;
}

void CCharacter::Output()
{
    CObject::Output();
    std::cout << "Attack: "<<mAtk<< std::endl;
    std::cout << "Defense: "<<mDef << std::endl;
    std::cout << "HP: " <<mHP<<"/"<<mHPMax<< std::endl;
    std::cout << "Level: "<<mLevel<< std::endl;
    std::cout << "Exp: "<<mExp << std::endl;
}

//CCharacter* CCharacter::Clone()
//{
//    return nullptr;
//}
