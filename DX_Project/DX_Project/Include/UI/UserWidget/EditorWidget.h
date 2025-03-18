#pragma once
#include "UserWidget.h"
class CEditorWidget :
    public CUserWidget
{
	friend class CSceneUIManager;
protected:
	CEditorWidget ();
	virtual ~CEditorWidget();
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
};

