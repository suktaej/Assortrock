#include "ObjectManager.h"
#include "Player.h"
CObjectManager* CObjectManager::mInst;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
    CreateObj<CPlayer>();
	return true;
}

void CObjectManager::Update(float DeltaTime)
{
    //for(CObject*& Obj : mObjList)
    std::list<CObject*>::iterator iter;
    std::list<CObject*>::iterator iterEnd = mObjList.end();

    for (iter = mObjList.begin();iter != iterEnd;iter++)
        (*iter)->Update(DeltaTime);
}

void CObjectManager::Output(char* OutputBuffer)
{
    std::list<CObject*>::iterator iter;
    std::list<CObject*>::iterator iterEnd = mObjList.end();

    for (iter = mObjList.begin();iter != iterEnd;iter++)
        (*iter)->Output(OutputBuffer);
}
