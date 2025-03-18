#pragma once
#include "UserWidget.h"
class CD1Widget :
    public CUserWidget
{
	friend class CSceneUIManager;

protected:
	CD1Widget();
	virtual ~CD1Widget();
public:
	virtual bool Init();
};
