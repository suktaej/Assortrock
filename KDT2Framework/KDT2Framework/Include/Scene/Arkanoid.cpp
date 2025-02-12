#include "Arkanoid.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Component/StaticMeshComponent.h"
#include "../Object/ArkPlayer.h"
#include "../Object/ArkBlock.h"
#include "../Object/ArkWall.h"
#include "../Object/ArkBall.h"

CArkanoid::CArkanoid()
{
}

CArkanoid::~CArkanoid()
{
}

bool CArkanoid::Init()
{
    if (!CScene::Init())
        return false;

    CArkPlayer* Player = CreateObj<CArkPlayer>("Player");

    CArkBlock* Block = CreateObj<CArkBlock>("Block");
    Block->SetWorldPos(0.f, 300.f);

    CArkWall* RWall = CreateObj<CArkWall>("RWall");
    //RWall->SetWorldPos(620.f, 0.f);
    RWall->SetWorldPos(200.f, 0.f);
    CArkWall* LWall = CreateObj<CArkWall>("LWall");
    LWall->SetWorldPos(-620.f, 0.f);

    CArkWall* TWall = CreateObj<CArkWall>("TWall");
    TWall->SetWorldPos(0.f, 340.f);
    TWall->SetWorldRotationZ(90.f);

    CArkWall* Pit = CreateObj<CArkWall>("Pit");
    Pit->SetWorldPos(0.f, -340.f);
    Pit->SetWorldRotationZ(90.f);

    return true;
}
