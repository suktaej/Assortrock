#include "ActiveSkill.h"

CActiveSkill::CActiveSkill()
{
}

CActiveSkill::~CActiveSkill()
{
}

void CActiveSkill::CreateSkill(const char* InputName, ESkillType InputType, int InputCoolDown)
{
	strcpy_s(mName,sizeof(mName), InputName);
	mType = InputType;
	mCoolDown = InputCoolDown;
}

