#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(const CMonster& Obj) :
	CCharacter(Obj)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
    CCharacter::Init();

    while (true)
    {
        std::cout << "1.����" << std::endl;
        std::cout << "2.����" << std::endl;
        std::cout << "3.�����" << std::endl;
        std::cout << "���̵�: ";
        int Input;
        std::cin >> Input;


        if (Input < 1 || Input >3)
            continue;
        mBattleType = (EBattleType)(Input - 1);
        break;
    }

    return true;
}

void CMonster::Output()
{
    CCharacter::Output();
    switch (mBattleType)
    {
    case EBattleType::Easy:
        std::cout << "���̵�: ����" << std::endl;
        break;
    case EBattleType::Normal:
        std::cout << "���̵�: ����" << std::endl;
        break;
    case EBattleType::Hard:
        std::cout << "���̵�: �����" << std::endl;
        break;
    }
}

void CMonster::Save(FILE* File)
{
    CCharacter::Save(File);
    //fwrite(&mBattleType, sizeof(EBattleType), 1, File);
}

CMonster* CMonster::Clone()
{
    return new CMonster(*this);
}
