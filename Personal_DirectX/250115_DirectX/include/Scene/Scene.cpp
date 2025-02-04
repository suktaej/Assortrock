#include "Scene.h"
#include "../Object/SceneObject.h"
#include "Input.h"
#include "CameraManager.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	SAFE_DELETE(mInput);
	SAFE_DELETE(mCameraManager);
}

bool CScene::Init()
{
	mInput = new CInput;
	
	if (!mInput->Init())
		return false;

	mCameraManager = new CCameraManager;

	if (!mCameraManager->Init())
		return false;

    return true;
}

bool CScene::Init(const char* FileName)
{
	mInput = new CInput;

	if (!mInput->Init())
		return false;

	mCameraManager = new CCameraManager;

	if (!mCameraManager->Init())
		return false;

    return true;
}

void CScene::PreUpdate(float DeltaTime)
{
    std::list<CSharedPtr<CSceneObject>>::iterator iter = mObjList.begin();
    std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

    while (iter != iterEnd)
    {
        if (!(*iter)->IsActive())
        {
            //erase를 할 경우 iteraotr의 다음 iterator를 반환
            iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
            continue;
        }
        else if (!(*iter)->IsEnable())
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
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
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
	mCameraManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
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

void CScene::Input(float DeltaTime)
{
	mInput->Update(DeltaTime);
}

void CScene::PreRender()
{
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
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
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
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
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
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
