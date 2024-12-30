#include "ObjectManager.h"
#include "Player.h"
#include "Item.h"
#include "Stage.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	CreateObj<CPlayer>();
    
	for (int i = 0;i < mItemSize;i++)
    {
        CItem* Item = nullptr;
        Item = CreateObj<CItem>();
        Item->SetPos((rand() % 13)+1, (rand() % 13) + 1);
    }

	return true;
}

void CObjectManager::Update(float DeltaTime)
{
	std::list<CObject*>::iterator	iter;
	std::list<CObject*>::iterator	iterEnd = mObjList.end();

	iter = mObjList.begin();
	while(iter != iterEnd)
	{
		(*iter)->Update(DeltaTime);
		++iter;

		if (CStage::GetInst()->GetDeath())
			return;
	}

	std::cout<<CStage::GetInst()->GetDeath();
	/*if (mObjList.size() >= 2)
	{
		iter = mObjList.begin();
		
		iterEnd = mObjList.end();
		iterEnd--;

		while (iter != iterEnd)
		{
			std::list<CObject*>::iterator iter1 = iter;
			iter1++;

			std::list<CObject*>::iterator iter1End = mObjList.end();

			while (iter1 != iter1End)
			{
				if ((*iter)->GetPos().X == (*iter1)->GetPos().X &&
					(*iter)->GetPos().Y == (*iter1)->GetPos().Y)
				{
					bool ItemCollison = false;
				}
			}
		}
	}*/
}

void CObjectManager::Output(char* Buffer)
{
	std::list<CObject*>::iterator	iter;
	std::list<CObject*>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Output(Buffer);
	}
}
