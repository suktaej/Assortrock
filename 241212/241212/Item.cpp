#include "Item.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

bool CItem::Init(FILE* File)
{
	fread(mName, sizeof(char), 32, File);
	fread(&mItemType, sizeof(EItemType), 1, File);
	fread(&mOption, sizeof(int), 1, File);
	fread(&mBuy, sizeof(int), 1, File);
	fread(&mSell, sizeof(int), 1, File);
	return true;
}

void CItem::Output()
{
    std::cout << "이름 : " << mName << std::endl;

    switch (mItemType)
    {
    case EItemType::Weapon:
        std::cout << "종류 : 무기" << std::endl;
        std::cout << "공격력 : " << mOption << std::endl;
        break;
    case EItemType::Armor:
        std::cout << "종류 : 방어구" << std::endl;
        std::cout << "방어력 : " << mOption << std::endl;
        break;
    }

    std::cout << "구매금액 : " << mBuy << std::endl;
    std::cout << "판매금액 : " << mSell << std::endl;
    std::cout << "------------" << std::endl;
}
