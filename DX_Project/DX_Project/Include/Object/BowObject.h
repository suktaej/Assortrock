#pragma once
#include "WeaponObject.h"
class CBowObject :
    public CWeaponObject
{
public:
    CBowObject();
    CBowObject(const CWeaponObject& Obj);
    CBowObject(CWeaponObject&& Obj);
    virtual ~CBowObject();

public:
    bool Init() final;
};

