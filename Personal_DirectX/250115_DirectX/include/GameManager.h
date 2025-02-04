#pragma once
#include "GameInfo.h"

class CGameManager
{
	DECLARE_SINGLE(CGameManager)
private:
	static bool m_Loop;
	HINSTANCE m_hInst = 0;
	HWND m_hWnd = 0;
	HDC m_hdc = 0;
	TCHAR m_ClassName[256] = {};
	TCHAR m_TitleName[256] = {};

	float m_ClearColor[4] = {};

public:
	bool Init(HINSTANCE hInst);
	int Run();
	HINSTANCE GetWindowInstance() const { return m_hInst; }
	HWND GetWindowHandle() const { return m_hWnd; }
private:
	void RegisterWindowClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Create();
private:
	void Logic();
	void Input(float DeltaTime);
	void Update(float DeltaTime);
	//void PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	//void PostCollisionUpdate(float DeltaTime);
	void Render(float DeltaTime);
};

