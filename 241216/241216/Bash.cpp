#include "Bash.h"

CBash::CBash()
{
}

CBash::CBash(const CBash& Obj)  :
    CSkillActive(Obj)
{
}

CBash::~CBash()
{
}

bool CBash::Init()
{
    strcpy_s(mName, "Bash");
    mMP = 10;
    mAttack = 30;

    return true;
}

bool CBash::Init(FILE* File)
{
    return true;
}

void CBash::Output()
{
}

CBash* CBash::Clone()
{
    return new CBash(*this);
}
