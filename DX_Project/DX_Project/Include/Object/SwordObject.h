#pragma once
#include "WeaponObject.h"
class CSwordObject :
    public CWeaponObject
{
public:
    CSwordObject();
    CSwordObject(const CWeaponObject& Obj);
    CSwordObject(CWeaponObject&& Obj);
    virtual ~CSwordObject();

public:
    bool Init() final;
};

