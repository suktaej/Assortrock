#pragma once
#include "Item.h"
class CItemScore :
    public CItem
{
public:
    CItemScore();
    ~CItemScore() override;
public:
    bool Init() override;
    void Output(char* OutputBuffer) override;
};

