#pragma once
#include "Object.h"

class CPlayer:public CObject
{
public:
	CPlayer();
	~CPlayer() override;
public:
	bool Init() override;
	void Update() override;
	void Output() override;
	void Output(char* OutBuffer,int CountX) override;
};

