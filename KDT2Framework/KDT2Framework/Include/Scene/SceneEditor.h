#pragma once

#include "Scene.h"

class CSceneEditor :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneEditor();
	virtual ~CSceneEditor();

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();
};

