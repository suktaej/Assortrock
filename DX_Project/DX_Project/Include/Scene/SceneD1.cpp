#include "SceneD1.h"
#include "../Object/PlayerObject.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Component/StaticMeshComponent.h"
#include "SceneAssetManager.h"
#include "../Asset/Material/Material.h"
#include "SceneUIManager.h"
#include "../Object/TileMapObj.h"
#include "../Object/EnemySmallSkel.h"

CSceneD1::CSceneD1()
{
}

CSceneD1::~CSceneD1()
{
}

bool CSceneD1::InitAsset()
{
    return true;
}

bool CSceneD1::InitObject()
{  
    //타일맵 생성
    CTileMapObj* TileMapObj = CreateObj<CTileMapObj>("D1TileMap");

    TCHAR	FullPath[MAX_PATH] = {};
    //타일맵 호출
    lstrcpy(FullPath, gRootPath);
    lstrcat(FullPath, TEXT("Asset\\Data\\D1TileMap.tlm"));

    TileMapObj->Load(FullPath);

    //플레이어 생성
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    //몬스터 생성
    CMonsterObject* Skel1 = CreateObj<CEnemySmallSkel>("SmallSkel");
    Skel1->SetWorldPos(300.f, 120.f);
    //Skel1->SetTarget(Player);
    
    return true;
}

bool CSceneD1::InitWidget()
{
   // CD1Widget* Widget = mUIManager->CreateWidget<CStartWidget>("Start");
   // mUIManager->AddToViewport(Widget);

    return true;
}
