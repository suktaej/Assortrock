#include "Enemy.h"

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

void CEnemy::Output()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    std::cout << "E";
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
