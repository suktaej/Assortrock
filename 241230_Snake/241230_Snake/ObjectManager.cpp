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

		//if (CStage::GetInst()->GetDeath())
		//	return;
	}

	//std::cout<<CStage::GetInst()->GetDeath();

	if (mObjList.size() > 1)
	{
		iter = mObjList.begin();
		//iterEnd = mObjList.end();
		//iterEnd--;

		std::list<CObject*>::iterator ItemIter = iter;
		ItemIter++;

		std::list<CObject*>::iterator ItemIterEnd = mObjList.end();

		//bool IterErase = false;
		while (ItemIter != ItemIterEnd)
		{
			if ((*iter)->GetPos().X == (*ItemIter)->GetPos().X &&
				(*iter)->GetPos().Y == (*ItemIter)->GetPos().Y)
			{
				CStage::GetInst()->SetScore(100);

				SAFE_DELETE(*ItemIter);
				ItemIter = mObjList.erase(ItemIter);
				ItemIterEnd = mObjList.end();
				continue;
			}
			ItemIter++;
		}
	}
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
