#pragma once

#include "WindowWidget.h"

class CInventory :
    public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CInventory();
	virtual ~CInventory();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
};

