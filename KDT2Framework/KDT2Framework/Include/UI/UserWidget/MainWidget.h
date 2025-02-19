#pragma once

#include "UserWidget.h"

class CMainWidget :
    public CUserWidget
{
	friend class CSceneUIManager;

protected:
	CMainWidget();
	virtual ~CMainWidget();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
};

