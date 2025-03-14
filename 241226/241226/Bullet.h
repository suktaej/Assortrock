#pragma once
#include "Object.h"
class CBullet :
    public CObject
{
public:
    CBullet();
    ~CBullet();
//protected:
private:
    float mMoveX = 0.f;
    float mMoveY = 0.f;
    float mMoveDirX = 0.f;
    float mMoveDirY = 0.f;
public:
    bool Init() override;
    void Update(float DeltaTime) override;
    void Output(char* OutputBuffer) override;
	ECollisionType CollisionEnable(CObject* Dest) override;

    void SetMoveDir(float x, float y) { mMoveDirX = x; mMoveDirY = y; }
    int GetDamage() override { return 1; }
    bool Damage(int Dmg) override { return true; }
};

