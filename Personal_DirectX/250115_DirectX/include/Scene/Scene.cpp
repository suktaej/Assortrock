#include "Scene.h"
#include "../Object/SceneObject.h"
#include "Input.h"
#include "CameraManager.h"
#include "SceneCollision.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	SAFE_DELETE(mCollision);
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

	//충돌체 생성 시 씬 콜리전에 등록하도록 구현
	//하나의 목록으로 모든 충돌체를 가지고 있도록 
	//매 프레임 충돌이 발생한다면 별도의 시간을 부여하여 제어할 수 있도록 함
	mCollision = new CSceneCollision;
	
	if (!mCollision->Init())
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
	mCollision->Update(DeltaTime);
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
