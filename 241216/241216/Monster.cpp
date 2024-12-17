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
	std::cout << "CMonster Init" << std::endl;

    return true;
}

CMonster* CMonster::Clone()
{
    return new CMonster(*this);
}
