#include "Enemy.h"
#include "Stage.h"
#include "StageManager.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
    return true;
}

void CEnemy::Output(char* OutputBuffer)
{
    //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    //std::cout << "E";
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '!';
}

void CEnemy::Update(float DeltaTime)
{
    mMoveY += DeltaTime;
    if (mMoveY >= 1.f)
    {
        mMoveY -= 1.f;
        ++mPos.Y;
    }
}
