#include "Device.h"

DEFINITION_SINGLE(CDevice)
CDevice::CDevice()
{
}
CDevice::~CDevice()
{
	SAFE_RELEASE(m_TargetView);
	SAFE_RELEASE(m_DepthView);
	SAFE_RELEASE(m_SwapChain);

	if (m_Context)
		m_Context->ClearState();

	SAFE_RELEASE(m_Context);
	SAFE_RELEASE(m_Device);
}

bool CDevice::Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode)
{
	m_hWnd = hWnd;
	m_RS.Width = Width;
	m_RS.Height = Height;

	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	//Direct2D, Direct3D ��ȣ��� Ȱ��ȭ
	//###
#ifdef _DEBUG
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
	//Debug ���� Ȱ��ȭ
#endif//_DEBUG
	//����� ��忡���� Ȱ���ϴ� �ڵ� �ۼ�

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	// FAILED ��ũ��
	// DirectX �Լ��� ��κ� HRESULT�� ��ȯ(long type)
	// 0 �̻��� ����, 0 �̸��� ����
	// ���޹��� HRESULT���� �˻��Ͽ� ������ ���(true) ��ȯ
	
	// Device�� DeviceContext�� �����ϴ� �Լ�
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, &FLevel,
		1, D3D11_SDK_VERSION, &m_Device, &FLevelResult, &m_Context)))
	{
		return false;
	}
	//ù��° ���� : ����� ���÷��� ��� ����
	// nullptr�� ���, �⺻ ��� ���
	//�ι�° ���� : ����̹� ���� ����
	//����° ���� : ����Ʈ���� ����̹� ��� �� ����̹� dll �ڵ� ����
	// nullptr�� ��� ������� ����
	//�׹�° ���� : ����̽� ���� �ɼ�
	//�ټ���° ���� : �����ϴ� Direct3D ��ɼ���(Feature Level)�� �迭������
	// DirectX�� ����
	//������° ���� : �ټ���° ������ �迭 ũ��
	//�ϰ���° ���� : Direct3D SDK ����
	//������° ���� : ������ Direct3D '����̽� ��ü(m_Device)'�� ��ȯ�޴� ���������
	//��ȩ��° ���� : ������ ����̽��� �����ϴ� ��ɼ����� ��ȯ�޴� ���������
	// �Է����� ��û�� ��� �� ���� ������������ ����
	//����° ���� : ������ ����̽� ���ؽ�Ʈ ��ü�� ��ȯ�޴� ��� ������

	//������ deivce�� �̿��Ͽ� �����Ǵ� ��Ƽ���ø� ���� ȹ��
	//��Ƽ���ø�(MSAA:Multi Sample Anti Aliasing) 
	//DX���� �⺻������ �����ϴ� ��Ƽ�������
	unsigned int SampleCount = 4;
	unsigned int Check = 0;

	//DXGI_FORMAT Ȯ��
	//���� 1 : ����ۿ� ����� �ȼ� ����
	//UNORM 0~1������ ���� 
	//DX�� 0~1������ ������ ���
	//���� 2 : ��û�ϴ� ��Ƽ���ø��� ���� ��
	//���� 3 : �����Ǵ� ����Ƽ ������ ������ ��ȯ�ٵ� ��°�
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

	//��ȯ���� ��°�(Check)�� 0���� �۴ٸ� ��û�� ���� ��(����2:4)�� �������� ����
	//���� ���� 1�� ����
	if (Check < 1)
		SampleCount = 1;

	//SwapChain ���� ���� ����ü
	//���� ���۸� �Ǵ� ��Ƽ���۸��� �����ϱ� ���� ��ü
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};
	//###

	//����ü���� ����ؼ� ����� ����
	//BufferDesc : �����ۿ� ���� ����
	SwapDesc.BufferDesc.Width = Width;
	SwapDesc.BufferDesc.Height = Height;

	//����� �ȼ� ����
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//ȭ�� �ֻ��� (1/60)
	//VSync(��������ȭ) �»�ܿ��� ���ϴܱ��� �ȼ��� �׷���
	//��� �ȼ��� �׷��� ��� VSync�� Ȱ��ȭ
	//��� �ȼ��� �׷��� ���Ŀ� �ð��� ���ƿ� ������ ��� �� ���
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;		//����
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;	//�и�

	//�ػ��� �����ϸ� ����� ����
	//���� â�� ū �ػ󵵸� ǥ���ؾ� �� ���(1280x720 ���� 1920x1080�� ����� ��)
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//��ĵ������ ��¼����� ����
	//������� �� ������ �о���̴� ���
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
	//������� ���� ����
	//������ �ø��� ����� ����� ��� 2�� �̻� ���� ����
	SwapDesc.BufferCount = 1;

	//������ �뵵�� ����
	//Render Target : GPU�� �׷��� �����͸� ������ �� �� ����ϴ� ��� ǥ��(surface)
	//ȭ�鿡 ����ϱ� �� ��� �ȼ� �����͸� �����(Render Target)�� �׸�
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//����� ������ �ڵ�����
	SwapDesc.OutputWindow = hWnd;

	//���� ��ũ����
	//��Ƽ���ø�(MSAA:Multi Sample Anti Aliasing) 
	//DX���� �⺻������ �����ϴ� ��Ƽ�������
	//�ӵ��� ����
	//FXAA : �����ƿ��� �����ϴ� ��Ƽ������� ���
	//�ֱ� ���� ����

	//��Ƽ���ø� ����Ƽ ����
	SwapDesc.SampleDesc.Quality = 0;
	//��Ƽ���ø� ���� ��
	SwapDesc.SampleDesc.Count = SampleCount;

	//������ ��� ����
	SwapDesc.Windowed = WindowMode;
	
	//SwapChain�� ���۸� ��ȯ�� ��(������ �ø���) ����ϴ� ������ ����
	//���� ������� ������ ��� ó���� ���ΰ� ����
	//DXGI_SWAP_EFFECT_DISCARD : ���� ������ �����ϰ� ��ȯ
	//DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL: ���������� ��ȯ
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Direct3D Device�� DXGI�� �����ϴ� �������̽�
	//�̹� ������� ���� �޾ƿ��� ����
	IDXGIDevice* DXGIDevice = nullptr;
	//###

	//Device ��ü���� ������ �������̽��� ������ �Լ�
	// DirectX ��ü�� DXGI ��ü �� ���� ����
	//REFIID : 
	//���� �������̽��� iid�� ����Ͽ� ���� id�� �����ϴ��� Ȯ��
	//__uuidof : DirectX�� IDXGIDevice �������̽��� �ش��ϴ� ������ ID ����
	//��ü�� ������ ���ο��� AddRef�� ����
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	//DXGI ���
	//DXGIDevice�� �θ�ü�� IDXGIAdapter�� ������
	//����ʹ� �׷��� ī��� ����� ��ü��, GPU�� ���÷��� ������ ����
	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter),(void**)&Adapter);

	//������� �θ� ��ü�� IDXGIFactory�� ������
	//���丮�� DirectX���� �׷��� ���ҽ� ��ü(����ü�� ��)�� �����ϱ� ���� �������̽�
	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)Factory);

	//Factory�� ����� ����ü�� ����
	if (FAILED(Factory->CreateSwapChain(m_Device, &SwapDesc, &m_SwapChain)))
	{
		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(DXGIDevice);
		return false;
	}
	
	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(DXGIDevice);

	//SwapChain���� ����۸� ����
	ID3D11Texture2D* BackBuffer = nullptr;

	//GetBuffer ȣ��� ���۸� ������ AddRef�� ȣ��� ����
	//Getbuffer(0)�� ù��° ����(�����)�� ��ȯ
	//���н� false�� ��ȯ
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;
	
	//����ۿ� ����ϱ� ���� ����Ÿ�ٺ並 ����
	//���� �ٰ��� GPU�� ȭ�鿡 �׸� ���� �����͸� ����� ǥ��
	if (FAILED(m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView)))
		return false;

	//Release ȣ��
	//������ ����ī��Ʈ(RefCount) ����
	//������ ���� Ÿ�� �並 ���������Ƿ� ����۸� ���������� �ʿ� ����
	SAFE_RELEASE(BackBuffer);

	//����,���ٽ� ���۸� ������ֱ� ���� Texture ����
	D3D11_TEXTURE2D_DESC DepthDesc = {};

	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;
	
	//D24 : ���̿� 24��Ʈ�� UNORM(0 ~ 1)
	//S8 : ���ٽǿ� 8��Ʈ�� UINT(0 ~ 255)
	//24bit�� ��� 
	//0~1 ���� ��� 8bit�� ���ٽǿ� unsigned int
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	//���̹��� �ؽ�ó
	ID3D11Texture2D* DepthBuffer = nullptr;

	//������ ������ ���̹��ۿ� Texture ����
	if (FAILED(m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	//����,���ٽ� �� ����
	if (FAILED(m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView)))
		return false;

	//���̹��� ����
	SAFE_RELEASE(DepthBuffer);

//����Ʈ ����(float type)
	D3D11_VIEWPORT VP = {};

	//ȭ�鿡 �������� ������ ����
	VP.Width = (float)Width;
	VP.Height = (float)Height;
	VP.MaxDepth = 1.f;
	
	//������ ���������ο��� �����Ͷ����� ��������(RS)�� ����Ʈ�� ����
	m_Context->RSSetViewports(1, &VP);

	return true;
}

void CDevice::ClearBackBuffer(float ClearColor[4])
{
	//�� �����Ӹ��� �����(Ÿ�ٺ䰡 ����۸� �����Ƿ�?)�� ������ �ʱ�ȭ
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::SetTarget()
{
	//��� �� ���� ������ ���� Ÿ�ٰ� �����並 ���� 
	//Ÿ���� �ѹ��� ���� ���� ����?
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Render()
{
	//�Ϲ����� ������ �ø���
	m_SwapChain->Present(0, 0);
}

