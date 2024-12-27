#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer() override;
private:
    int mHP = 5;
    int mHPMax = 5;
public:
    bool Init() override;
    void Update(float DeltaTime) override;
    void Output(char* OutputBuffer) override;
    bool Damage(int Dmg) override;
	ECollisionType CollisionEnable(CObject* Dest) override;
public:
    int GetHP() { return mHP; }
    void SetHP(int Val) { mHP += Val; }
};

