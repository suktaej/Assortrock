#pragma once
#include "GameInfo.h"

class CDevice
{
	DECLARE_SINGLE(CDevice)
private:
	//GPU�� �������̽� ����
	ID3D11Device* m_Device = nullptr;
	//GPU�� ����� �����ϴ� ����
	ID3D11DeviceContext* m_Context = nullptr;
	//������ �ø��� ó��
	IDXGISwapChain* m_SwapChain = nullptr;
	//���� Ÿ�� ����
	ID3D11RenderTargetView* m_TargetView = nullptr;
	//���� ���� ����
	ID3D11DepthStencilView* m_DepthView = nullptr;

	//�ػ� ó���� ���� ����� ����ü ����
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


