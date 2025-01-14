#pragma once
#include "GameInfo.h"
#include "Share/Timer.h"

class CGameManager
{
	DECLARE_SINGLE(CGameManager)
private:
	static bool m_Loop;
	HINSTANCE m_hInst = 0;
	HWND m_hWnd = 0;
	HDC m_hdc = 0;
	TCHAR m_ClassName[MAX_STRING] = {};
	TCHAR m_TitleName[MAX_STRING] = {};

	//RECT m_RC = { 100,100,200,200 };
	FRect m_RC = { 100,100,200,200 };
	FRect m_Enemy = { 1000,100,1100,200 };
	float m_EnemyDir = 1.f;
	bool m_bEnemyMove = true;

	std::list<FRect> m_BulletList;
	std::list<FRect> m_EnemyBulletList;
	float m_EnemyBulletCreate = 0.f;

public:
	bool Init(HINSTANCE hInst);
	int Run();
private:
	void RegisterWindowClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Create();
private:
	void Logic();
	void Input(float DeltaTime);
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void PostCollisionUpdate(float DeltaTime);
	void Render(float DeltaTime);
};

