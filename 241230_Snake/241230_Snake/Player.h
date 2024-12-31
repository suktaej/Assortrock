#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
public:
	CPlayer();
	~CPlayer() override;
private:
	float mMove = 0.f;
	int mDirX = 0;
	int mDirY = 0;

	int mScore = 0;
public:
	bool Init() override;
	void Update(float) override;
	void Output(char* Buffer) override;
	void SetScore(int Num) { mScore += Num; }
};

