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
	//lstrcpy(m_ClassName, TEXT(""));	�����ڵ� �ؽ�Ʈ ��ũ��
	lstrcpy(m_ClassName, L"FrameWork");
	lstrcpy(m_TitleName, L"FrameWork");

	RegisterWindowClass();
    
    if (!Create())
        return false;

    //���ڷ� �� �����쿡 ����� �� �ִ� DC�� ����
    //GetDC�� ���� ���ڴ� �Ҹ��ڿ��� ReleaseDC ����
    m_hdc = GetDC(m_hWnd);
    
    //Device �ʱ�ȭ
    if (!CDevice::GetInst()->Init(m_hWnd, 1280, 720, true))
        return false;
    //���̴� ������ �ʱ�ȭ
    if (!CShaderManager::GetInst()->Init())
        return false;
    //���� ������ �ʱ�ȭ
    if (!CAssetManager::GetInst()->Init())
        return false;

    //Ÿ�̸� �ʱ�ȭ
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
            // Ű���� �Է� �޼����� �߻��� ��� �����Ѵ�.
            // WM_KEYDOWN, WM_KEYUP �� �޼����� �߻��ϸ� ������ ��� WM_CHAR �޼����� �ϳ���
            // ������ִ� ������ �Ѵ�.
            TranslateMessage(&msg);

            // �޼����� WndProc�� �������ش�.
            DispatchMessage(&msg);
        }

        // ������ ����Ÿ���� ��� �����Ѵ�.(�޼��� ť�� �޼����� ���� ���)
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

    // ������Ŭ���� ����ü�� ũ�⸦ ��Ÿ����. �ݵ�� �����Ǿ�� �Ѵ�.
    wcex.cbSize = sizeof(WNDCLASSEX);

    // ȭ�鿡 ��°����� ������ Ŭ���̾�Ʈ �����̶�� �Ѵ�.
    // Ŭ���̾�Ʈ ������ ũ��(����, ����)�� ����� �� ���� �ٽ� �׷��ֵ��� �Ѵ�.
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // �޼���ť���� ���� �޼����� ���ڷ� �־ ȣ������ �Լ��� �ּҸ� �Ѱ��ش�.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // �ü������ �ο����� HINSTANCE�� �����Ѵ�.
    wcex.hInstance = m_hInst;

    // �������� �������� �����Ѵ�.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    // ������ â������ Ŀ�� ����� ��Ÿ����.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    // Ŭ���̾�Ʈ ������ ������ �����Ѵ�.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // ������ �޴��� �����Ѵ�.
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY250113WINDOW);
    // 0�� �����ϸ� �޴��� ���ش�.
    wcex.lpszMenuName = 0;

    // ����� ������Ŭ������ �̸��� �����Ѵ�.
    wcex.lpszClassName = m_ClassName;

    // ������â ���� ����� ���� �������� �����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // ������ ������ ������Ŭ������ ����Ѵ�.
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
    // ������ â ����޼���
    case WM_DESTROY:
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        // ������ ������ �޼��� ���� �ٸ� �޼����� �߻��� ��� �������� �⺻ ��������
        // ó���� �ǰ� ������ش�.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    return LRESULT();
}

bool CGameManager::Create()
{
    m_hWnd = CreateWindowW(m_ClassName, m_TitleName, WS_OVERLAPPEDWINDOW,
        100, 100, 1280, 720, nullptr, nullptr, m_hInst, nullptr);
    //������ â ��ü�� ũ��(Ÿ��Ʋ ��, ƽ ������(â�� �ø��� ����))
    //������ ������ ������ ũ��� Ÿ��Ʋ �� ���� ũ�Ⱑ ��� ������ ũ��� ����

    if (!m_hWnd)
        return false;
    //RECT ����ü Ÿ��
    RECT WindowRC = { 0,0,1280,720 };
    //Ŭ���̾�Ʈ ������ 1280,720�� �Ǳ� ���� �ʿ��� ������ ��ü ũ�⸦ �������� �Լ�
    //(TickFrame,Meun, TitleBar ���� ���Ե� ��ü ũ��)
    //Ŭ���̾�Ʈ ������ ù��° ����(RECT ����ü)�� ũ�⸸ŭ ����
    AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);
    //�������� ��ġ�� ũ�⸦ ���� ȭ�鿡�� ����
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

    // ���
    CSharedPtr<CShader>  Shader = CShaderManager::GetInst()->FindShader("ColorMeshShader");
    CSharedPtr<CMesh>  Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("CenterRect");
    Shader->SetShader();
    Mesh->Render();
    
    CDevice::GetInst()->Render();
}
