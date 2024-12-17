#include "Character.h"

CCharacter::CCharacter()
{
	mObjType = EObjectType::Character;
}

CCharacter::CCharacter(const CCharacter& Obj)	:
	CObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	std::cout << "CCharacter Init" << std::endl;

	return true;
}

void CCharacter::Output()
{
	// 부모클래스의 Output함수를 호출한다.
	CObject::Output();


	//std::cout << "이름 : " << mName << std::endl;
	std::cout << "공격력 : " << mAttack <<
		"\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << " / " <<
		mHPMax << "\t마나 : " <<
		mMP << " / " << mMPMax << std::endl;
	std::cout << "레벨 : " << mLevel <<
		"\t경험치 : " << mExp << std::endl;
	std::cout << "소지금 : " << mGold << std::endl;
}

void CCharacter::CharacterExclusive()
{
}

void CCharacter::VirtualPure()
{
}

void CCharacter::VirtualPure1()
{
}

void CCharacter::VirtualPure2()
{
}

void CCharacter::VirtualPure3()
{
}
