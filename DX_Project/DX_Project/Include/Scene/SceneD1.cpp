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
    //Ÿ�ϸ� ����
    CTileMapObj* TileMapObj = CreateObj<CTileMapObj>("D1TileMap");

    TCHAR	FullPath[MAX_PATH] = {};
    //Ÿ�ϸ� ȣ��
    lstrcpy(FullPath, gRootPath);
    lstrcat(FullPath, TEXT("Asset\\Data\\D1TileMap.tlm"));

    TileMapObj->Load(FullPath);

    //�÷��̾� ����
    CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

    //���� ����
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
