#pragma once
#include "Character.h"

enum class EJob :unsigned char
{
	None,
	Fighter,
	Archer,
	Mage
};

class CPlayer : public CCharacter
{
public:
	CPlayer();
	~CPlayer();
protected:
	EJob mJob;
public:
	bool Init();
	void Output();
};

