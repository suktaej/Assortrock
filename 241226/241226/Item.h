#pragma once
#include "Object.h"
class CItem :
    public CObject
{
public:
    CItem();
    ~CItem() override;
protected:
    float mMoveX = 0.f;
    float mMoveY = 0.f;
    ECollisionType mCollisionType;
public:
    bool Init() override;
    void Update(float DeltaTime) override;
    void Output(char* OutputBuffer) override;
    ECollisionType CollisionEnable(CObject* Dest) override;

    ECollisionType GetCollisionType() { return mCollisionType;  }
};

