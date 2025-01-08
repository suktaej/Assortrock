#pragma once
#include "Object.h"
class FIBlock :
    public FObject
{
public:
    FIBlock();
    ~FIBlock() override;
public:
    bool Init() override;
    //void Update(float DeltaTime);
    void Output(char* Buffer) override;
};

