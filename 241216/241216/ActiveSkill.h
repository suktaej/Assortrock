#pragma once
#include "Skill.h"

class CActiveSkill :
    public CSkill
{
public:
    CActiveSkill();
    ~CActiveSkill();
private:
    int mCoolDown = 0;
public:
    void CreateSkill(const char*,ESkillType, int);
};

