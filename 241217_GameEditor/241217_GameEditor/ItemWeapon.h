#pragma once
#include "Item.h"
class CItemWeapon :
    public CItem
{
public:
	CItemWeapon();
	CItemWeapon(const CItemWeapon& Obj);
	~CItemWeapon();

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CItemWeapon* Clone();
};

