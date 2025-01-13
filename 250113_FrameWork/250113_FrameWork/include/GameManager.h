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

