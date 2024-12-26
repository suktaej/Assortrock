#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer() override;
private:
    //class CMap* mMap = nullptr;
public:
    bool Init() override;
    void Update() override;
    void Output() override;
    //void SetMap(class CMap* Map) { mMap = Map; }
};

