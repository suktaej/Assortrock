#include "Player.h"
#include "Item.h"

int gLevelUpTable[LEVEL_MAX - 1] =
{
	3000,
	5000,
	10000,
	20000,
	35000,
	55000,
	80000,
	110000,
	150000
};

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	std::cout << "이름 : ";
	std::cin >> mName;

	while (true)
	{
		std::cout << "1. 전사" << std::endl;
		std::cout << "2. 궁수" << std::endl;
		std::cout << "3. 마법사" << std::endl;
		std::cout << "직업을 선택하세요 : ";
		int	Job = 0;
		std::cin >> Job;

		if (Job <= (int)EJob::None ||
			Job >= (int)EJob::End)
			continue;

		mJob = (EJob)Job;
		break;
	}

	switch (mJob)
	{
	case EJob::Fighter:
		mAttack = 40;
		mDefense = 20;
		mHP = 500;
		mHPMax = 500;
		mMP = 100;
		mMPMax = 100;
		break;
	case EJob::Archer:
		mAttack = 50;
		mDefense = 15;
		mHP = 400;
		mHPMax = 400;
		mMP = 200;
		mMPMax = 200;
		break;
	case EJob::Mage:
		mAttack = 60;
		mDefense = 10;
		mHP = 300;
		mHPMax = 300;
		mMP = 300;
		mMPMax = 300;
		break;
	}

	mLevel = 1;
	mExp = 0;
	mGold = 100000;

	return true;
}

void CPlayer::Output()
{
	std::cout << "===========Player===========" << std::endl;
	std::cout << "이름 : " << mName << "\t" <<
		"직업 : ";

	switch (mJob)
	{
	case EJob::Fighter:
		std::cout << "전사" << std::endl;
		break;
	case EJob::Archer:
		std::cout << "궁수" << std::endl;
		break;
	case EJob::Mage:
		std::cout << "마법사" << std::endl;
		break;
	}

	std::cout << "레벨 : " << mLevel << 
		"\t경험치 : " << mExp << " / " << gLevelUpTable[mLevel - 1] << std::endl;
	std::cout << "공격력 : " << mAttack;
	if (mEquip[static_cast<int>(EEquip::Weapon)])
		std::cout << " + " << mEquip[static_cast<int>(EEquip::Weapon)]->GetOption();
	std::cout << "\t방어력 : " << mDefense;
	if (mEquip[static_cast<int>(EEquip::Armor)])
		std::cout << " + " << mEquip[static_cast<int>(EEquip::Armor)]->GetOption();
	std::cout << std::endl;
	std::cout << "체력 : " << mHP << " / " << mHPMax << 
		"\t마나 : " << mMP << " / " << mMPMax << std::endl;
	std::cout << "Gold : " << mGold << std::endl;
	
	std::cout << "장착무기 : ";
	if (mEquip[static_cast<int>(EEquip::Weapon)])
		std::cout << mEquip[static_cast<int>(EEquip::Weapon)]->GetName();
	else
		std::cout << "없음";

	std::cout << "\t장착방어구 : ";
	if (mEquip[static_cast<int>(EEquip::Armor)])
		std::cout << mEquip[static_cast<int>(EEquip::Armor)]->GetName() << std::endl;
	else
		std::cout << "없음" << std::endl;
}

int CPlayer::GetHP() { return mHP; }
int CPlayer::GetMaxHP() { return mHPMax; }
int CPlayer::GetATK() 
{	
	int ATK = mAttack;
	if (mEquip[static_cast<int>(EEquip::Weapon)])
		ATK += mEquip[static_cast<int>(EEquip::Weapon)]->GetOption();

	return ATK; 
}
int CPlayer::GetDEF() 
{	
	int DEF = mDefense;
	if (mEquip[static_cast<int>(EEquip::Armor)])
		DEF += mEquip[static_cast<int>(EEquip::Armor)]->GetOption();

	return DEF; 
}
int CPlayer::GetEXP() { return mExp; }
int CPlayer::GetGold() { return mGold; }

void CPlayer::SetHP(int NewHP) { mHP = NewHP; }
void CPlayer::SetGold(int NewGold) { mGold += NewGold; }
CItem* CPlayer::Equip(CItem* Item)		{
	
	EEquip EquipType;

	switch (Item->GetType())
	{
	case EItemType::Weapon:
		EquipType = EEquip::Weapon;
		break;
	case EItemType::Armor:
		EquipType = EEquip::Armor;
		break;
	}

	CItem* ReturnItem = nullptr;		

	if (nullptr == mEquip[static_cast<int>(EquipType)])	//장착부위에 아이템이 없을 경우 장착
		mEquip[static_cast<int>(EquipType)] = Item;
	else
	{
		ReturnItem = mEquip[static_cast<int>(EquipType)];
		mEquip[static_cast<int>(EquipType)] = Item;
	}
	return ReturnItem;
}
CItem* CPlayer::GetEquipItem(EEquip Type)
{
	return mEquip[static_cast<int>(Type)];
}
void CPlayer::SetResult(int NewExp, int NewGold)
{
	mExp += NewExp;
	mGold += NewGold;
}

void CPlayer::Resurrection()
{
	mHP = mHPMax;
	mMP = mMPMax;
	mExp *= 0.9f;
	mGold *= 0.9f;
}
bool CPlayer::Damage(int Dmg)
{
	mHP -= Dmg;
	if (mHP <= 0)
		return true;
	return false;
}
