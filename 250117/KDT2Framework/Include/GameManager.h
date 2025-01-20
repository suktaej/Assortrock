#pragma once

#include "GameInfo.h"

class CGameManager
{
private:
	static bool	mLoop;
	HINSTANCE	mhInst = 0;
	HWND		mhWnd = 0;
	HDC			mhDC = 0;
	TCHAR		mClassName[256] = {};
	TCHAR		mTitleName[256] = {};

	float		mClearColor[4] = {};

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void PostCollisionUpdate(float DeltaTime);
	void Render(float DeltaTime);

private:
	void RegisterWindowClass();
	bool Create();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};

