#pragma once
#include "Object.h"
class FTBlock :
    public FObject
{
public:
    FTBlock();
    ~FTBlock() override;
public:
    bool Init() override;
    //void Update(float DeltaTime);
    void Output(char* Buffer) override;
};


