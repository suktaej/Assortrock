#include "Character.h"

CCharacter::CCharacter()
{
	mObjType = EObjectType::Character;
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	std::cout << "Char init" << std::endl;
	return true;
}

void CCharacter::Output()
{
	CObject::Output();
}

void CCharacter::SetCharaterInfo(int ATK, int DEF, int HP, int MP)
{
	mAttack = ATK;
	mDef
}
