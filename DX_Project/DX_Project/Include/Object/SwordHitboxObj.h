#pragma once
#include "HitboxObj.h"

class CSwordHitboxObj :
    public CHitboxObj
{
public:
    CSwordHitboxObj();
    CSwordHitboxObj(const CSwordHitboxObj& Obj);
    CSwordHitboxObj(CSwordHitboxObj&& Obj);
    virtual ~CSwordHitboxObj();

public:
    bool Init() final;
    void Update(float DeltaTime) final;

public:
    void CollisionAttack(const FVector3D& HitPoint, class CColliderBase* Dest) final;
};
