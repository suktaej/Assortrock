#include "ObjectManager.h"
#include "Object.h"
#include "IBlock.h"

FObjectManager* FObjectManager::s_Inst = nullptr;

FObjectManager::FObjectManager()
{
}

FObjectManager::~FObjectManager()
{
}

bool FObjectManager::Init()
{
	return true;
}

void FObjectManager::Update(float DeltaTime)
{
	//std::list<FObject*>::iterator iter = m_BlockList.begin();
	//std::list<FObject*>::iterator iterEnd = m_BlockList.end();

	//while(iter!=iterEnd)
	//{
	//	(*iter)->Update(DeltaTime);
	//	iter++;
	//}
}

void FObjectManager::Output(char* OutputBuffer)
{
	std::list<FObject*>::iterator	iter;
	std::list<FObject*>::iterator	iterEnd = m_BlockList.end();

	for (iter = m_BlockList.begin(); iter != iterEnd; ++iter)
		(*iter)->Output(OutputBuffer);
}
