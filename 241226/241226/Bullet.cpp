#include "Bullet.h"
#include "StageManager.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
    return true;
}

void CBullet::Update(float DeltaTime)
{
    mMoveX += mMoveDirX * DeltaTime * 7.f;
    mMoveY += mMoveDirY * DeltaTime * 7.f;

    //mMoveX는 왼쪽으로 갈 경우 -1보다 작거나 같다
    //mMoveX는 오른쪽으로 갈 경우 1보다 크거나 같다
    //mMoveY는 아래로 갈 경우 1보다 크거나 같다
    //mMoveY는 위로 갈 경우 1보다 작거나 같다
    //abs : 절대값 함수
    if (abs(mMoveY) >= 1.f)
    {
        mPos.Y += (int)mMoveY;
        mMoveY -= (int)mMoveY;
        //분석필요
    }
    if (abs(mMoveX) >= 1.f)
    {
        mPos.X += (int)mMoveX;
        mMoveX -= (int)mMoveX;
    }

}

void CBullet::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '*';
}
