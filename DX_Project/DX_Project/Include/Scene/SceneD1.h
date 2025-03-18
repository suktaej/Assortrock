#pragma once
#include "Scene.h"

class CSceneD1 :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneD1();
	virtual ~CSceneD1();

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();
};

