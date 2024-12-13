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
    std::cout << "�̸� : " << mName << std::endl;

    switch (mItemType)
    {
    case EItemType::Weapon:
        std::cout << "���� : ����" << std::endl;
        std::cout << "���ݷ� : " << mOption << std::endl;
        break;
    case EItemType::Armor:
        std::cout << "���� : ��" << std::endl;
        std::cout << "���� : " << mOption << std::endl;
        break;
    }

    std::cout << "���űݾ� : " << mBuy << std::endl;
    std::cout << "�Ǹűݾ� : " << mSell << std::endl;
    std::cout << "------------" << std::endl;
}
