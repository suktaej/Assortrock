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
    
    //for (int i = 0;i < 5;i * 64)
    //{
    //    for (int j = 0;j < 4;j * 32)
    //    {

    //    }
    //}
    CArkBlock* Block = CreateObj<CArkBlock>("Block");
    Block->SetWorldPos(0.f, 300.f);
    CArkBlock* Block1 = CreateObj<CArkBlock>("Block");
    Block1->SetWorldPos(64.f, 300.f);
    CArkBlock* Block2 = CreateObj<CArkBlock>("Block");
    Block2->SetWorldPos(-64.f, 300.f);
    CArkBlock* Block3 = CreateObj<CArkBlock>("Block");
    Block3->SetWorldPos(128.f, 300.f);
    CArkBlock* Block4 = CreateObj<CArkBlock>("Block");
    Block4->SetWorldPos(-128.f, 300.f);
    CArkBlock* Block5 = CreateObj<CArkBlock>("Block");
    Block5->SetWorldPos(0.f, 268.f);

    CArkWall* RWall = CreateObj<CArkWall>("RWall");
    RWall->SetWorldPos(350.f, 0.f);
    CArkWall* LWall = CreateObj<CArkWall>("LWall");
    LWall->SetWorldPos(-350.f, 0.f);
    CArkWall* TWall = CreateObj<CArkWall>("TWall");
    TWall->SetWorldPos(0.f, 350.f);
    TWall->SetWorldRotationZ(90.f);

    //CArkWall* Pit = CreateObj<CArkPit>("Pit");
    //Pit->SetWorldPos(0.f, -340.f);
    //Pit->SetWorldRotationZ(90.f);

    return true;
}
