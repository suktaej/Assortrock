#pragma once
#include "Object.h"
class CEnemy :
    public CObject
{
public:
    CEnemy();
    ~CEnemy() override;
protected:
    float mMoveX = 0.f;
    float mMoveY = 0.f;
public:
    bool Init() override;
    void Output() override;
    void Update(float DeltaTime) override;
};

