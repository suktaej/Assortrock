#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init(FILE* File)
{
	//클래스 내 멤버변수 크기만큼 사이즈가 할당
	fread(mName, sizeof(char), 32, File);
	fread(&mAttack, sizeof(int), 1, File);
	fread(&mDefense, sizeof(int), 1, File);
	fread(&mHP, sizeof(int), 1, File);
	fread(&mHPMax, sizeof(int), 1, File);
	fread(&mMP, sizeof(int), 1, File);
	fread(&mMPMax, sizeof(int), 1, File);
	fread(&mLevel, sizeof(int), 1, File);
	fread(&mExp, sizeof(int), 1, File);
	fread(&mGold, sizeof(int), 1, File);

	return true;
}

void CMonster::Output()
{
	std::cout << "===========Monster===========" << std::endl;
	std::cout << "이름 : " << mName << std::endl;

	std::cout << "레벨 : " << mLevel <<
		"\t경험치 : " << mExp << std::endl;
	std::cout << "공격력 : " << mAttack <<
		"\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << " / " <<
		mHPMax << "\t마나 : " << mMP <<
		" / " << mMPMax << std::endl;
	std::cout << "Gold : " << mGold << std::endl;
}

CMonster* CMonster::Clone()
{
	//CMonster 타입의 새로운 객체를 생성하고 주소를 반환
	//*this 를 사용하여 자신을 복제한 새로운 객체를 생성
	//복사생성자의 사용 예
	return new CMonster(*this);
}

int CMonster::GetHP() { return mHP; }
int CMonster::GetATK() { return mAttack; }
int CMonster::GetDEF() { return mDefense; }
int CMonster::GetEXP() { return mExp; }
int CMonster::GetGold() { return mGold; }
char* CMonster::GetName() { return mName; }

void CMonster::SetHP(int NewHP) { mHP = NewHP; }

bool CMonster::Damage(int Dmg)
{
	mHP -= Dmg;
	if ( mHP <= 0)
		return true;
	return false;
}
