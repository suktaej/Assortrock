#pragma once
#include "Object.h"
class CTrap :
    public CObject
{
public:
    CTrap();
    ~CTrap();
public:
    bool Init() override;
    void Update() override;
    void Output(char* OutBuffer, int CountX) override;
};

