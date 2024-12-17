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
	std::cout << "CCharacter init" << std::endl;
	return true;
}

void CCharacter::Output()
{
	CObject::Output();
	std::cout << "공격력 : " << mAttack <<
		"\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << " / " <<
		mHPMax << "\t마나 : " <<
		mMP << " / " << mMPMax << std::endl;
	std::cout << "레벨 : " << mLevel <<
		"\t경험치 : " << mExp << std::endl;
	std::cout << "소지금 : " << mGold << std::endl;
}

void CCharacter::SetCharaterInfo(int ATK, int DEF, int HP, int MP)
{
	mAttack = ATK;
	mDefense = DEF;
	mHP = HP;
	mHPMax = HP;
	mMP = MP;
	mMPMax = MP;
}
