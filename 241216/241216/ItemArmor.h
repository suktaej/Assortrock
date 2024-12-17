#pragma once
#include "Item.h"
class CItemArmor :
    public CItem
{
public:
	CItemArmor();
	CItemArmor(const CItemArmor& Obj);
	~CItemArmor();

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CItemArmor* Clone();
};

