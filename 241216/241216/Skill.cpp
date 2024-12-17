#include "Skill.h"

CSkill::CSkill()
{
}

CSkill::CSkill(const CSkill& Obj)   :
    CObject(Obj)
{
}

CSkill::~CSkill()
{
}

bool CSkill::Init()
{
    return true;
}

bool CSkill::Init(FILE* File)
{
    return true;
}

void CSkill::Output()
{
}

CSkill* CSkill::Clone()
{
    return new CSkill(*this);
}

void CSkill::VirtualPure()
{
}

void CSkill::VirtualPure1()
{
}

void CSkill::VirtualPure2()
{
}

void CSkill::VirtualPure3()
{
}
