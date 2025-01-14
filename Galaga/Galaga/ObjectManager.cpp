#include "ObjectManager.h"
#include "Player.h"

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
	std::list<CObject*>::iterator iter = m_ObjList.begin();
	std::list<CObject*>::iterator iterEnd = m_ObjList.end();

	while (iter != iterEnd)
	{
		(*iter)->Update(DeltaTime);

		if (!(*iter)->GetActive())
		{
			SAFE_DELETE(*iter);
			iter = m_ObjList.erase(iter);
			continue;
		}
		iter++;
	}

	if (m_ObjList.size() >= 2)
	{
		iterEnd = m_ObjList.end();
		iterEnd--;
	}

}

void CObjectManager::Output(char* Buffer)
{
}
