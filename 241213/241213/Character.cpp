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
	std::cout << "���ݷ� : " << mAttack <<
		"\t���� : " << mDefense << std::endl;
	std::cout << "ü�� : " << mHP << " / " <<
		mHPMax << "\t���� : " <<
		mMP << " / " << mMPMax << std::endl;
	std::cout << "���� : " << mLevel <<
		"\t����ġ : " << mExp << std::endl;
	std::cout << "������ : " << mGold << std::endl;
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
