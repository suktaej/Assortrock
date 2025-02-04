#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
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

    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    CMonsterObject* Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(400.f, 300.f);

    Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(-400.f, 300.f);

    Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(400.f, -300.f);

    Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(-400.f, -300.f);

    Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(900.f, 700.f);


    Monster = CreateObj<CNearingMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(-400.f, 0.f);

    return true;
}
