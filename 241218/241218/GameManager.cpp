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
//        //�̷� ����
//        //����ũ��,����ũ�� ����
//        //������ ���� ����
//        //0:��, 1:��, 2:������, 3:������
//    }
}
