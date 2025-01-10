#include "ObjectManager.h"
#include "Object.h"

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
	//std::list<FObject*>::iterator	iter;
	//std::list<FObject*>::iterator	iterEnd = m_BlockList.end();

	//for (iter = m_BlockList.begin(); iter != iterEnd; ++iter)
	//	(*iter)->Output();
}

void FObjectManager::RemoveBlock()
{
	if (!m_BlockList.empty())
	{
		FObject* Block = m_BlockList.front();
		delete Block;
		m_BlockList.pop_front();
	}
}
