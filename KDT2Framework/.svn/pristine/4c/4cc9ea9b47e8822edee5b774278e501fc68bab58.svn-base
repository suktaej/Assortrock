#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Component/StaticMeshComponent.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::Init()
{
    if (!CScene::Init())
        return false;

    CPlayerObject* Obj = CreateObj<CPlayerObject>("Player");

    return true;
}
