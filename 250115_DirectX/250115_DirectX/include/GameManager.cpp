#include "GameManager.h"
#include "resource.h"
#include "Share/Timer.h"
#include "Asset/AssetManager.h"
#include "Device.h"
#include "Shader/ShaderManager.h"

#include "Asset/Mesh/MeshManager.h"
#include "Asset/Mesh/Mesh.h"
#include "Shader/Shader.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
    CAssetManager::DestroyInst();
    CDevice::DestroyInst();
    CShaderManager::DestroyInst();

    ReleaseDC(m_hWnd, m_hdc);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
	//lstrcpy(m_ClassName, TEXT(""));	유니코드 텍스트 매크로
	lstrcpy(m_ClassName, L"FrameWork");
	lstrcpy(m_TitleName, L"FrameWork");

	RegisterWindowClass();
    
    if (!Create())
        return false;

    //인자로 들어간 윈도우에 출력할 수 있는 DC가 생성
    //GetDC로 얻어온 인자는 소멸자에서 ReleaseDC 실행
    m_hdc = GetDC(m_hWnd);
    
    //Device 초기화
    if (!CDevice::GetInst()->Init(m_hWnd, 1280, 720, true))
        return false;
    //셰이더 관리자 초기화
    if (!CShaderManager::GetInst()->Init())
        return false;
    //에셋 관리자 초기화
    if (!CAssetManager::GetInst()->Init())
        return false;

    //타이머 초기화
    CTimer::Init();

	return true;
}

int CGameManager::Run()
{
    MSG msg;

    while (m_Loop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 키보드 입력 메세지가 발생할 경우 동작한다.
            // WM_KEYDOWN, WM_KEYUP 등 메세지가 발생하면 문자일 경우 WM_CHAR 메세지를 하나더
            // 만들어주는 역할을 한다.
            TranslateMessage(&msg);

            // 메세지를 WndProc로 전달해준다.
            DispatchMessage(&msg);
        }

        // 윈도우 데드타임일 경우 동작한다.(메세지 큐에 메세지가 없는 경우)
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::RegisterWindowClass()
{
    WNDCLASSEXW wcex;

    // 윈도우클래스 구조체의 크기를 나타낸다. 반드시 지정되어야 한다.
    wcex.cbSize = sizeof(WNDCLASSEX);

    // 화면에 출력가능한 영역을 클라이언트 영역이라고 한다.
    // 클라이언트 영역의 크기(가로, 세로)가 변경될 시 전부 다시 그려주도록 한다.
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // 메세지큐에서 얻어온 메세지를 인자로 넣어서 호출해줄 함수의 주소를 넘겨준다.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // 운영체제에서 부여해준 HINSTANCE를 전달한다.
    wcex.hInstance = m_hInst;

    // 실행파일 아이콘을 지정한다.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    // 윈도우 창에서의 커서 모양을 나타낸다.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    // 클라이언트 영역의 색상을 지정한다.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // 윈도우 메뉴를 지정한다.
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY250113WINDOW);
    // 0을 대입하면 메뉴를 없앤다.
    wcex.lpszMenuName = 0;

    // 등록할 윈도우클래스의 이름을 지정한다.
    wcex.lpszClassName = m_ClassName;

    // 윈도우창 좌측 상단의 작은 아이콘을 지정한다.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // 위에서 설정한 윈도우클래스를 등록한다.
    RegisterClassExW(&wcex);
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;
    // 윈도우 창 종료메세지
    case WM_DESTROY:
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        // 위에서 지정한 메세지 외의 다른 메세지가 발생할 경우 윈도우의 기본 동작으로
        // 처리가 되게 만들어준다.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    return LRESULT();
}

bool CGameManager::Create()
{
    m_hWnd = CreateWindowW(m_ClassName, m_TitleName, WS_OVERLAPPEDWINDOW,
        100, 100, 1280, 720, nullptr, nullptr, m_hInst, nullptr);
    //윈도우 창 전체의 크기(타이틀 바, 틱 프레임(창을 늘리는 막대))
    //위에서 지정한 윈도우 크기는 타이틀 바 등의 크기가 모두 합쳐진 크기로 지정

    if (!m_hWnd)
        return false;
    //RECT 구조체 타입
    RECT WindowRC = { 0,0,1280,720 };
    //클라이언트 영역이 1280,720이 되기 위해 필요한 윈도우 전체 크기를 가져오는 함수
    //(TickFrame,Meun, TitleBar 등이 포함된 전체 크기)
    //클라이언트 영역을 첫번째 인자(RECT 구조체)의 크기만큼 조정
    AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);
    //윈도우의 위치와 크기를 실제 화면에서 설정
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, WindowRC.right - WindowRC.left, 
        WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);
    
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return true;
}

void CGameManager::Logic()
{
    float DeltaTime = CTimer::Update();
    Input(DeltaTime);
    Update(DeltaTime);
    PostUpdate(DeltaTime);
    Collision(DeltaTime);
    PostCollisionUpdate(DeltaTime);
    Render(DeltaTime);
}


void CGameManager::Input(float DeltaTime)
{
   }

void CGameManager::Update(float DeltaTime)
{
    }

void CGameManager::PostUpdate(float DeltaTime)
{
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::PostCollisionUpdate(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
    CDevice::GetInst()->ClearBackBuffer(m_ClearColor);
    CDevice::GetInst()->ClearDepthStencil(1.f, 0);
    CDevice::GetInst()->SetTarget();

    // 출력
    CSharedPtr<CShader>  Shader = CShaderManager::GetInst()->FindShader("ColorMeshShader");
    CSharedPtr<CMesh>  Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("CenterRect");
    Shader->SetShader();
    Mesh->Render();
    
    CDevice::GetInst()->Render();
}
