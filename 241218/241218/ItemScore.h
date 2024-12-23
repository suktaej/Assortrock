#pragma once
#include "Item.h"
class CItemScore :
    public CItem
{
public:
    CItemScore();
    ~CItemScore();
public:
    bool Init() override;
    void Update() override;
    void Output(char* OutBuffer, int CountX) override;
};

