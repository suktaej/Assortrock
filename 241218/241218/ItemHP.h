#pragma once
#include "Item.h"
class CItemHP :
    public CItem
{
public:
    CItemHP();
    ~CItemHP();
public:
    bool Init() override;
    void Update() override;
    void Output(char* OutBuffer, int CountX) override;
};

