#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
public:
    bool Init() override;
    void Update() override;
    void Output() override;
};

