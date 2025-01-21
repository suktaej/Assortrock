#include "SceneManager.h"
#include "SceneMain.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{

}

bool CSceneManager::Init()
{
	m_CurrentScene = CreateScene<CSceneMain>();
	return true;
}

void CSceneManager::Update(float DeltaTime)
{
	m_CurrentScene->PreUpdate(DeltaTime);
	m_CurrentScene->Update(DeltaTime);
	m_CurrentScene->PostUpdate(DeltaTime);
}

void CSceneManager::Render()
{
	m_CurrentScene->PreRender();
	m_CurrentScene->Render();
	m_CurrentScene->PostRender();
}

void CSceneManager::Input(float DeltaTime)
{
	m_CurrentScene->Input(DeltaTime);
}

void CSceneManager::Collision(float DeltaTime)
{
}
