#pragma once
#include "Object.h"
class CItem :
    public CObject
{
public:
    CItem();
    ~CItem();
private:
    int mCount = 10;
public:
    bool Init() override;
    void Update(float) override;
    void Output(char*) override;

    void SetCount(int Num) { mCount = Num; }
    int GetCount() { return mCount; }
};
