#pragma once
#include "HitboxObj.h"
class CMonsterHitboxObj :
    public CHitboxObj
{
public:
    CMonsterHitboxObj();
    CMonsterHitboxObj(const CMonsterHitboxObj& Obj);
    CMonsterHitboxObj(CMonsterHitboxObj&& Obj);
    virtual ~CMonsterHitboxObj();

public:
    bool Init() final;
    void Update(float DeltaTime) final;

public:
    void CollisionAttack(const FVector3D& HitPoint, class CColliderBase* Dest) final;
};
