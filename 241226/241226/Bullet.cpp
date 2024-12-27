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

    //mMoveX�� �������� �� ��� -1���� �۰ų� ����
    //mMoveX�� ���������� �� ��� 1���� ũ�ų� ����
    //mMoveY�� �Ʒ��� �� ��� 1���� ũ�ų� ����
    //mMoveY�� ���� �� ��� 1���� �۰ų� ����
    //abs : ���밪 �Լ�
    if (abs(mMoveY) >= 1.f)
    {
        mPos.Y += (int)mMoveY;
        mMoveY -= (int)mMoveY;
        //�м��ʿ�
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
