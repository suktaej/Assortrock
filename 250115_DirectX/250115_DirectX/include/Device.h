#pragma once
#include "GameInfo.h"

class CDevice
{
	DECLARE_SINGLE(CDevice)
private:
	//GPU와 인터페이스 역할
	ID3D11Device* m_Device = nullptr;
	//GPU에 명령을 전달하는 역할
	ID3D11DeviceContext* m_Context = nullptr;
	//페이지 플리핑 처리
	IDXGISwapChain* m_SwapChain = nullptr;
	//랜더 타겟 생성
	ID3D11RenderTargetView* m_TargetView = nullptr;
	//깊이 버퍼 생성
	ID3D11DepthStencilView* m_DepthView = nullptr;

	//해상도 처리를 위한 사용자 구조체 생성
	FResolution m_RS;
	HWND m_hWnd;
	bool m_WindowMode = true;
public:
	ID3D11Device* GetDevice() const { return m_Device; }
	ID3D11DeviceContext* GetContext() const{ return m_Context; }
	IDXGISwapChain* GetSwapChain() const { return m_SwapChain; }
	const FResolution& GetResolution() const { return m_RS; }
	bool GetWindowMode() const { return m_WindowMode; }

public:
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode);
	void ClearBackBuffer(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void SetTarget();
	void Render();
};


