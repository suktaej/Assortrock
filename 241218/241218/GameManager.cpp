#include "GameManager.h"
#include "MazeManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

bool CGameManager::Init()
{
    CMazeManager::GetInst()->Init();
    return true;
}

void CGameManager::Run()
{
    CMazeManager::GetInst()->Run();
//    while (true)
//    {
//        //미로 생성
//        //가로크기,세로크기 지정
//        //파일을 통해 생성
//        //0:길, 1:벽, 2:시작점, 3:도착점
//    }
}
