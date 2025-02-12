#pragma once
#include "Scene.h"

class CArkanoid :
	public CScene
{
	friend class CSceneManager;

private:
	CArkanoid();
	virtual ~CArkanoid();

public:
	virtual bool Init();
};

