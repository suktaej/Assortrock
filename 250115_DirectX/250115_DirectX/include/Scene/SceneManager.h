#pragma once
#include "../GameInfo.h"

class CSceneManager
{
DECLARE_SINGLE(CSceneManager)

private:
	class CScene* m_CurrentScene = nullptr;
public:
	bool Init();
	void Update(float DeltaTime);
	void Render();
	void Input(float DeltaTime);
	void Collision(float DeltaTime);
public:
	template<typename T>
	T* CreateScene()
	{
		T* Scene = new T;
		if (!Scene->Init())
		{
			SAFE_DELETE(Scene);
			return nullptr;
		}
		return Scene;
	}
};

