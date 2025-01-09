#pragma once
#include "Object.h"
class FHealItem :
    public FObject
{
public:
	FHealItem();
	~FHealItem();
public:
	bool Init() override;
	void Update() override;
	void Output(char* Buffer, int CountX) override;
};

