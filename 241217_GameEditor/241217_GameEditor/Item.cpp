#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& Obj)  :
    CObject(Obj)
{
    mType = Obj.mType;
}

CItem::~CItem()
{
}

bool CItem::Init()
{
    CObject::Init();

    std::cout << "Option: ";
    std::cin >> mOption;

    std::cout << "Buy Cost: ";
    std::cin >> mBuy;
    
    std::cout << "Sell Cost: ";
    std::cin >> mSell;
    return true;
}

bool CItem::Init(FILE* File)
{
    CObject::Init(File);

    fread(&mType, sizeof(EItemType), 1, File);
    fread(&mOption, sizeof(int), 1, File);
    fread(&mBuy, sizeof(int), 1, File);
    fread(&mSell, sizeof(int), 1, File);

    return true;
}

void CItem::Output()
{
    std::cout << "Buy Cost : " << mBuy <<
        std::endl;
    std::cout << "Sell Cost : " << mSell <<
        std::endl;
}

void CItem::Save(FILE* File)
{
    CObject::Save(File);
    fwrite(&mType, sizeof(EItemType),1,File);
    fwrite(&mOption, sizeof(int),1,File);
    fwrite(&mBuy, sizeof(int),1,File);
    fwrite(&mSell, sizeof(int),1,File);
}


CItem* CItem::Clone()
{
    return new CItem(*this);
}
