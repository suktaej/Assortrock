#include "Scene.h"
#include "../Object/SceneObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

bool CScene::Init()
{
    return true;
}

bool CScene::Init(const char* FileName)
{
    return true;
}

void CScene::PreUpdate(float DeltaTime)
{
    std::list<CSharedPtr<CSceneObject>>::iterator iter = m_ObjList.begin();
    std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = m_ObjList.end();

    while (iter != iterEnd)
    {
        if (!(*iter)->IsActive())
        {
            //erase�� �� ��� iteraotr�� ���� iterator�� ��ȯ
            m_ObjList.erase(iter);
            continue;
        }
        else if ((*iter)->IsEnable())
        {
            iter++;
            continue;
        }
        
        (*iter)->PreUpdate(DeltaTime);
        iter++;
    }
}

void CScene::Update(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ�Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);

		++iter;
	}
}

void CScene::PostUpdate(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ�Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);

		++iter;
	}
}

void CScene::Collision(float DeltaTime)
{
}

void CScene::PreRender()
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ�Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreRender();

		++iter;
	}
}

void CScene::Render()
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ�Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();

		++iter;
	}
}

void CScene::PostRender()
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ�Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostRender();

		++iter;
	}
}