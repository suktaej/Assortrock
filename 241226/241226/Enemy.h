#pragma once
#include "Object.h"
class CEnemy :
    public CObject
{
public:
    CEnemy();
    ~CEnemy() override;
private:
    int mHP = 1;
    int mHPMax = 1;
protected:
    float mMoveX = 0.f;
    float mMoveY = 0.f;
    float mFireTime = 0.f;
public:
    bool Init() override;
    void Output(char* OutputBuffer) override;
    void Update(float DeltaTime) override;
	ECollisionType CollisionEnable(CObject* Dest) override;
    bool Damage(int Dmg) override;

    int GetDamage() override { return 1; }
};

