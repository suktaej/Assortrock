#pragma once
#include "Object.h"
class FDamageItem :
    public FObject
{
public:
	FDamageItem();
	~FDamageItem();
public:
	bool Init() override;
	void Update() override;
	void Output(char* Buffer, int CountX) override;
};

