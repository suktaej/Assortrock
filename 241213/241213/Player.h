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
	void SetJob(EJob);
	//virtual void Output();		//자식 노드일 경우 virtual을 붙이지 않아도 무관하지 않나?
	void Output() override;
};
