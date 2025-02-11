#pragma once
#include "MonsterObject.h"
class CGunnerMonster :
    public CMonsterObject
{
    friend class CScene;

protected:
    CGunnerMonster();
    CGunnerMonster(const CGunnerMonster& Obj);
    CGunnerMonster(CGunnerMonster&& Obj);
    ~CGunnerMonster() override;

protected:
    float       mFireTime = 1.f;
    int         mFireCount = 0;

public:
    bool Init() override;
    void Update(float DeltaTime) override;
     
};

