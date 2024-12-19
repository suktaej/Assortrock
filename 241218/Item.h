#pragma once
#include "Object.h"
class CItem :
    public CObject
{
public:
    CItem();
    ~CItem();
private:
public:
    bool Init() override;
    void Update() override;
    void Output(char* OutBuffer,int CountX) override;
};

