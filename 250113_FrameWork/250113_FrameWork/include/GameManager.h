#pragma once
#include "GameInfo.h"
#include "Share/Timer.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

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

	FVector2D m_PlayerPos = { 150.f, 150.f };
	FVector2D m_PlayerSize = { 100.f, 100.f };
	FVector2D m_EnemyPos = { 1050.f, 150.f };
	FVector2D m_EnemySize = { 100.f, 100.f };
	float m_EnemyDir = 1.f;

	std::list<FBullet> m_BulletList;
	std::list<FBullet> m_EnemyBulletList;
	
	float m_FireTime = 1.f;
	float m_FireAccTime = 0.f;


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

