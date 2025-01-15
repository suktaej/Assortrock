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
	//Direct2D, Direct3D 상호운용 활성화
	//###
#ifdef _DEBUG
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
	//Debug 정보 활성화
#endif//_DEBUG
	//디버그 모드에서만 활용하는 코드 작성

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	// FAILED 매크로
	// DirectX 함수는 대부분 HRESULT를 반환(long type)
	// 0 이상은 성공, 0 미만은 실패
	// 전달받은 HRESULT값을 검사하여 실패한 경우(true) 반환
	
	// Device와 DeviceContext를 생성하는 함수
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, &FLevel,
		1, D3D11_SDK_VERSION, &m_Device, &FLevelResult, &m_Context)))
	{
		return false;
	}
	//첫번째 인자 : 사용할 디스플레이 어뎁터 지정
	// nullptr일 경우, 기본 어뎁터 사용
	//두번째 인자 : 드라이버 유형 지정
	//세번째 인자 : 소프트웨어 드라이버 사용 시 드라이버 dll 핸들 지정
	// nullptr일 경우 사용하지 않음
	//네번째 인자 : 디바이스 생성 옵션
	//다섯번째 인자 : 지원하는 Direct3D 기능수준(Feature Level)의 배열포인터
	// DirectX의 버전
	//여섯번째 인자 : 다섯번째 인자의 배열 크기
	//일곱번째 인자 : Direct3D SDK 버전
	//여덟번째 인자 : 생성된 Direct3D '디바이스 객체(m_Device)'를 반환받는 출력포인터
	//아홉번째 인자 : 생성된 디바이스가 지원하는 기능수준을 반환받는 출력포인터
	// 입력으로 요청한 기능 중 가장 높은수준으로 설정
	//열번째 인자 : 생성된 디바이스 컨텍스트 객체를 반환받는 출력 포인터

	//생성된 deivce를 이용하여 지원되는 멀티샘플링 수를 획득
	//멀티샘플링(MSAA:Multi Sample Anti Aliasing) 
	//DX에서 기본적으로 지원하는 안티엘리어싱
	unsigned int SampleCount = 4;
	unsigned int Check = 0;

	//DXGI_FORMAT 확인
	//인자 1 : 백버퍼에 사용할 픽셀 포맷
	//UNORM 0~1사이의 색상값 
	//DX는 0~1사이의 색상값을 사용
	//인자 2 : 요청하는 멀티샘플링의 샘플 수
	//인자 3 : 지원되는 퀄리티 레벨의 개수를 반환바든 출력값
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

	//반환받은 출력값(Check)이 0보다 작다면 요청한 샘플 수(인자2:4)는 지원되지 않음
	//샘플 수를 1로 변경
	if (Check < 1)
		SampleCount = 1;

	//SwapChain 설정 정의 구조체
	//더블 버퍼링 또는 멀티버퍼링을 구현하기 위한 객체
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};
	//###

	//스왑체인을 사용해서 백버퍼 생성
	//BufferDesc : 벡버퍼에 대한 정의
	SwapDesc.BufferDesc.Width = Width;
	SwapDesc.BufferDesc.Height = Height;

	//백버퍼 픽셀 포맷
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//화면 주사율 (1/60)
	//VSync(수직동기화) 좌상단에서 우하단까지 픽셀로 그려냄
	//모든 픽셀을 그려낼 경우 VSync가 활성화
	//모든 픽셀을 그려낸 이후에 시간이 돌아올 때까지 대기 후 출력
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;		//분자
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;	//분모

	//해상도의 스케일링 방식을 설정
	//작은 창에 큰 해상도를 표현해야 할 경우(1280x720 에서 1920x1080를 출력할 때)
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//스캔라인의 출력순서를 설정
	//백버퍼의 한 라인을 읽어들이는 방법
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
	//백버퍼의 수를 지정
	//페이지 플리핑 방식을 사용할 경우 2개 이상 설정 가능
	SwapDesc.BufferCount = 1;

	//버퍼의 용도를 지정
	//Render Target : GPU가 그래픽 데이터를 랜더링 할 때 사용하는 출력 표면(surface)
	//화면에 출력하기 전 모든 픽셀 데이터를 백버퍼(Render Target)에 그림
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//출력할 윈도우 핸들지정
	SwapDesc.OutputWindow = hWnd;

	//샘플 디스크립션
	//멀티샘플링(MSAA:Multi Sample Anti Aliasing) 
	//DX에서 기본적으로 지원하는 안티엘리어싱
	//속도가 느림
	//FXAA : 엔비디아에서 제공하는 안티엘리어싱 기능
	//최근 많이 사용됨

	//멀티샘플링 퀄리티 레벨
	SwapDesc.SampleDesc.Quality = 0;
	//멀티샘플링 샘플 수
	SwapDesc.SampleDesc.Count = SampleCount;

	//윈도우 모드 지정
	SwapDesc.Windowed = WindowMode;
	
	//SwapChain이 버퍼를 전환할 때(페이지 플리핑) 사용하는 동작을 지정
	//이전 백버퍼의 내용을 어떻게 처리할 것인가 설정
	//DXGI_SWAP_EFFECT_DISCARD : 이전 내용을 무시하고 전환
	//DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL: 순차적으로 전환
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Direct3D Device를 DXGI와 연결하는 인터페이스
	//이미 만들어진 값을 받아오는 역할
	IDXGIDevice* DXGIDevice = nullptr;
	//###

	//Device 객체에서 지정된 인터페이스를 얻어오는 함수
	// DirectX 객체와 DXGI 객체 간 연동 설정
	//REFIID : 
	//쿼리 인터페이스는 iid를 사용하여 같은 id가 존재하는지 확인
	//__uuidof : DirectX의 IDXGIDevice 인터페이스에 해당하는 고유한 ID 생성
	//객체를 얻어오면 내부에서 AddRef를 진행
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	//DXGI 어뎁터
	//DXGIDevice의 부모객체인 IDXGIAdapter를 가져옴
	//어댑터는 그래픽 카드와 연결된 객체로, GPU와 디스플레이 설정을 관리
	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter),(void**)&Adapter);

	//어댑터의 부모 객체인 IDXGIFactory를 가져옴
	//팩토리는 DirectX에서 그래픽 리소스 객체(스왑체인 등)를 생성하기 위한 인터페이스
	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)Factory);

	//Factory를 사용해 스왑체인 생성
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

	//SwapChain에서 백버퍼를 얻어옴
	ID3D11Texture2D* BackBuffer = nullptr;

	//GetBuffer 호출로 버퍼를 얻어오면 AddRef가 호출된 상태
	//Getbuffer(0)은 첫번째 버퍼(백버퍼)를 반환
	//실패시 false를 반환
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;
	
	//백버퍼에 출력하기 위한 렌더타겟뷰를 생성
	//렌더 다겟은 GPU가 화면에 그릴 최종 데이터를 출력할 표면
	if (FAILED(m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView)))
		return false;

	//Release 호출
	//증가된 참조카운트(RefCount) 감소
	//위에서 렌더 타겟 뷰를 생성했으므로 백버퍼를 직접참조할 필요 없음
	SAFE_RELEASE(BackBuffer);

	//깊이,스텐실 버퍼를 만들어주기 위한 Texture 생성
	D3D11_TEXTURE2D_DESC DepthDesc = {};

	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;
	
	//D24 : 깊이에 24비트를 UNORM(0 ~ 1)
	//S8 : 스텐실에 8비트를 UINT(0 ~ 255)
	//24bit를 사용 
	//0~1 값을 사용 8bit는 스텐실용 unsigned int
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	//깊이버퍼 텍스처
	ID3D11Texture2D* DepthBuffer = nullptr;

	//위에서 정의한 깊이버퍼용 Texture 생성
	if (FAILED(m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	//깊이,스텐실 뷰 생성
	if (FAILED(m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView)))
		return false;

	//깊이버퍼 해제
	SAFE_RELEASE(DepthBuffer);

//뷰포트 생성(float type)
	D3D11_VIEWPORT VP = {};

	//화면에 렌더링할 영역을 정의
	VP.Width = (float)Width;
	VP.Height = (float)Height;
	VP.MaxDepth = 1.f;
	
	//랜더링 파이프라인에서 레스터라이저 스테이지(RS)에 뷰포트를 설정
	m_Context->RSSetViewports(1, &VP);

	return true;
}

void CDevice::ClearBackBuffer(float ClearColor[4])
{
	//매 프레임마다 백버퍼(타겟뷰가 백버퍼를 가지므로?)의 색상을 초기화
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::SetTarget()
{
	//출력 시 값을 저장할 렌더 타겟과 뎁스뷰를 지정 
	//타겟을 한번에 여럿 생성 가능?
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Render()
{
	//일반적인 페이지 플리핑
	m_SwapChain->Present(0, 0);
}

