#include "SceneMain.h"
#include "../Component/StaticMeshComponent.h"
#include "../Object/PlayerObject.h"
//#include "../Object/MonsterObject.h"

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
    
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");
    //CMonsterObject* Monster = CreateObj<CMonsterObject>("Monster");
    
    //Monster->SetTarget(Player);
    //Monster->SetWorldPos(400.f, 300.f);
    return true;
}
