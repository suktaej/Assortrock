#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
#include "../Object/ObjectSpawnPoint.h"
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

    CObjectSpawnPoint* MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster1");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(400.f, 300.f);

    MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster2");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(-400.f, 300.f);

    MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster3");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::OnceDestroy);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(400.f, -300.f);

    MonsterPoint =
        CreateObj<CObjectSpawnPoint>("Monster3");

    MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
    MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
    MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
    MonsterPoint->SetDestroySpawnCount(3);
    MonsterPoint->SetSpawnTime(3.f);
    MonsterPoint->SetImmediateSpawn(true);
    MonsterPoint->SetWorldPos(-400.f, -300.f);

    CMonsterObject* Monster = CreateObj<CGunnerMonster>("Monster");

    Monster->SetWorldPos(900.f, 700.f);


    Monster = CreateObj<CNearingMonster>("Monster");

    Monster->SetTarget(Player);

    Monster->SetWorldPos(-400.f, 0.f);

    return true;
}
