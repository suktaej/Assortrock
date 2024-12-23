#pragma once
#include "Object.h"
class CCharacter :
    public CObject
{
public:
    CCharacter();
    CCharacter(const CCharacter& Obj);
    ~CCharacter();

protected:
    int mAtk;
    int mDef;
    int mHP;
    int mHPMax;
    int mLevel = 1;
    int mExp = 0;
    int mGold = 10000;

public:
    void SetInfo(int atk, int def, int hp)
    {
        mAtk = atk;
        mDef = def;
        mHPMax = hp;
        mHP = mHPMax;
    }
public:
    bool Init() override;
    void Output() override;
    //CCharacter* Clone() override;
};

