#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Component/StaticMeshComponent.h"
#include "SceneAssetManager.h"
#include "../Asset/Material/Material.h"
#include "../UI/UserWidget/MainWidget.h"
#include "SceneUIManager.h"
#include "../Object/TileMapObj.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::InitAsset()
{
    mAssetManager->CreateMaterial("Monster1");

    CMaterial* Material =
        mAssetManager->FindMaterial("Monster1");

    Material->SetPixelShader("DefaultMaterialShader");
    Material->SetSamplerType(ETextureSamplerType::Linear);
    Material->AddTexture("Monster1", TEXT("Texture/block_wall.png"),
        0);

    mAssetManager->LoadSound("Hit", "Effect", false, "Sound/Fire1.wav");

    return true;
}

bool CSceneMain::InitObject()
{
    //타일맵 생성
    CTileMapObj* TileMapObj = CreateObj<CTileMapObj>("TileMap");

    TCHAR	FullPath[MAX_PATH] = {};
    //타일맵 호출
    lstrcpy(FullPath, gRootPath);
    lstrcat(FullPath, TEXT("Asset\\Data\\TileMap.tlm"));

    TileMapObj->Load(FullPath);
    
    //플레이어 생성
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    /*CObjectSpawnPoint* MonsterPoint =
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

    Monster->SetWorldPos(-400.f, 0.f);*/

    return true;
}

bool CSceneMain::InitWidget()
{
    CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("Main");

    mUIManager->AddToViewport(Widget);

    return true;
}
