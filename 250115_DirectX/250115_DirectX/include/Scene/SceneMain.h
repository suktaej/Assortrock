#pragma once
#include "Scene.h"

class CSceneMain :
    public CScene
{
	friend class CSceneManager;
private:
    CSceneMain();
    ~CSceneMain() override;
public:
    bool Init() override;
};

