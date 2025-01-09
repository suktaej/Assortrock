#pragma once
#include "Object.h"
class FScoreItem :
    public FObject
{
public:
    FScoreItem();
    ~FScoreItem() override;
public:
	bool Init() override;
	void Update() override;
	void Output(char* Buffer, int CountX) override;

};

