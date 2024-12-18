#include "Character.h"

CCharacter::CCharacter()
{
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
	CObject::Init();
	std::cout << "공격력: ";
	std::cin >> mAttack;
	std::cout << "방어력: ";
	std::cin >> mDefense;
	std::cout << "최대체력: ";
	std::cin >> mHPMax;
	std::cout << "최대마력: ";
	std::cin >> mMPMax;
	std::cout << "레벨: ";
	std::cin >> mLevel;
	std::cout << "경험치: ";
	std::cin >> mExp;
	std::cout << "골드: ";
	std::cin >> mGold;
	mHP = mHPMax;
	mMP = mMPMax;
	
	return true;
}

bool CCharacter::Init(FILE* File)
{
	return true;
}

void CCharacter::Output()
{
	CObject::Output();
	std::cout << "공격력: " << mAttack <<
		"\t방어력: " << mDefense << std::endl;
	std::cout << "체력: " << mHP << " / " <<
		mHPMax << "\t마나: " <<
		mMP << " / " << mMPMax << std::endl;
	std::cout << "레벨: " << mLevel <<
		"\t경험치: " << mExp << std::endl;
	std::cout << "소지금: " << mGold << std::endl;
}

void CCharacter::Save(FILE* File)
{
	CObject::Save(File);
	fwrite(&mAttack, sizeof(int), 1, File);
	fwrite(&mDefense, sizeof(int), 1, File);
	fwrite(&mHP, sizeof(int), 1, File);
	fwrite(&mHPMax, sizeof(int), 1, File);
	fwrite(&mMP, sizeof(int), 1, File);
	fwrite(&mMPMax, sizeof(int), 1, File);
	fwrite(&mLevel, sizeof(int), 1, File);
	fwrite(&mExp, sizeof(int), 1, File);
	fwrite(&mGold, sizeof(int), 1, File);
}
