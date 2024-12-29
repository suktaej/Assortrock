#pragma once
#include "Object.h"
class CItem :
    public CObject
{
public:
    CItem();
    ~CItem() override;
public:
    bool Init()override;
    void Update()override;
    void Output()override;
    void Output(char* OutBuffer, int CountX) override;

};

