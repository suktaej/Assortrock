#include "GameManager.h"
#include "resource.h"
#include "Share/Timer.h"
#include "Device.h"

#include "Share/Log.h"

TCHAR   gRootPath[MAX_PATH];

DEFINITION_SINGLE(CGameManager)

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
    //CProfileManager::DestroyInst();
    //CSceneManager::DestroyInst();
    //CAssetManager::DestroyInst();
    //CShaderManager::DestroyInst();
    CDevice::DestroyInst();

    ReleaseDC(mhWnd, mhDC);

    CLog::Destroy();
}

bool CGameManager::Init(HINSTANCE hInst)
{
    mhInst = hInst;

    lstrcpy(mClassName, TEXT("KDT2Framework"));
    lstrcpy(mTitleName, TEXT("KDT2Framework"));

    RegisterWindowClass();

    if (!Create())
        return false;

    if (!CLog::Init())
        return false;

    // ���ڷ� �� �����쿡 ����� �� �ִ� DC�� ���������.
    mhDC = GetDC(mhWnd);

    // ����̽� �ʱ�ȭ
    if (!CDevice::GetInst()->Init(mhWnd, 1280, 720, true))
        return false;

    //// Shader ������ �ʱ�ȭ
    //if (!CShaderManager::GetInst()->Init())
    //    return false;

    //// �ּ� ������ �ʱ�ȭ
    //if (!CAssetManager::GetInst()->Init())
    //    return false;

    //// Profile ������ �ʱ�ȭ
    //if (!CProfileManager::GetInst()->Init())
    //    return false;

    // Ÿ�̸� �ʱ�ȭ
    CTimer::Init();

    //// �������� �ʱ�ȭ
    //if (!CSceneManager::GetInst()->Init())
    //    return false;

    return true;
}

int CGameManager::Run()
{
    MSG msg;

    while (mLoop)
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

void CGameManager::Logic()
{
    float DeltaTime = CTimer::Update();
    Input(DeltaTime);
    Update(DeltaTime);
    Collision(DeltaTime);
    Render(DeltaTime);
}

void CGameManager::Input(float DeltaTime)
{
    //CSceneManager::GetInst()->Input(DeltaTime);
}

void CGameManager::Update(float DeltaTime)
{
    CLog::PrintLog("Update");

    static bool Push = false;

    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        Push = true;
    }

    else if (Push)
    {
        Push = false;
        CLog::SaveLog();
    }
    //CSceneManager::GetInst()->Update(DeltaTime);
}

void CGameManager::Collision(float DeltaTime)
{
    //CSceneManager::GetInst()->Collision(DeltaTime);
}

void CGameManager::Render(float DeltaTime)
{
    CDevice::GetInst()->ClearBackBuffer(mClearColor);
    CDevice::GetInst()->ClearDepthStencil(1.f, 0);
    CDevice::GetInst()->SetTarget();

    //CSceneManager::GetInst()->Render();

    CDevice::GetInst()->Render();
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
    wcex.hInstance = mhInst;

    // �������� �������� �����Ѵ�.
    wcex.hIcon = LoadIcon(mhInst, MAKEINTRESOURCE(IDI_ICON1));

    // ������ â������ Ŀ�� ����� ��Ÿ����.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    // Ŭ���̾�Ʈ ������ ������ �����Ѵ�.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // ������ �޴��� �����Ѵ�.
    // 0�� �����ϸ� �޴��� ���ش�.
    wcex.lpszMenuName = 0;

    // ����� ������Ŭ������ �̸��� �����Ѵ�.
    wcex.lpszClassName = mClassName;

    // ������â ���� ����� ���� �������� �����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // ������ ������ ������Ŭ������ ����Ѵ�.
    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    // CreateWindow : ������ â�� �������ִ� �Լ��̴�.
    // WinAPI���� �Լ���ڿ� W�� ������ �����ڵ�, A�� ������ ��Ƽ����Ʈ�̴�.
    // 1������ : ������ Ŭ���� �̸��� �����Ѵ�.
    // 2������ : ������ Ÿ��Ʋ�ٿ� ����� �̸��� �����Ѵ�.
    // 3������ : ������ â�� ����� �����Ѵ�.
    // 4������ : ȭ�鿡�� �����찡 ������ X������ �����Ѵ�.
    // 5������ : ȭ�鿡�� �����찡 ������ Y������ �����Ѵ�.
    // 6������ : ������ â�� ���� ũ�⸦ �����Ѵ�.
    // 7������ : ������ â�� ���� ũ�⸦ �����Ѵ�.
    // 8������ : �θ������찡 ���� ��� �θ��������� �ڵ��� �����Ѵ�.
    // 9������ : �޴� �ڵ��� �����Ѵ�.
    // 10������ : ������ �ν��Ͻ��� �����Ѵ�. WinMain���� ������ ������ �����ؾ� �Ѵ�.
    // 11������ : â ���� �����͸� �����Ѵ�. WM_CREATE�� ������ ������ �߻��ϴ� �޼����ε�
    // �� �޼����� �߻��ϸ� WndProc �Լ��� lParam�� �� ���� ���޵ȴ�.
    // �̷��� �����츦 �����ϸ� ������ �ڵ��� ������ش�.
    // �߸��� ������ ��� 0�� ��ȯ�Ѵ�.
    mhWnd = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
        100, 100, 1280, 720, nullptr, nullptr, mhInst, nullptr);

    if (!mhWnd)
    {
        return false;
    }

    // ������ Ŭ���̾�Ʈ ������ ũ�⸦ ���ϴ� ũ��� �����Ѵ�.
    // ������ ������ ������ ũ��� Ÿ��Ʋ�� ���� ũ�Ⱑ ��� ������ ũ��� �����ȴ�.
    RECT    WindowRC = { 0, 0, 1280, 720 };

    // Ŭ���̾�Ʈ ������ 1280, 720�� �Ǳ� ���� �ʿ��� ������ ��ü ũ�⸦ ���´�.
    // (ThickFrame, Menu, TitleBar ���� ���Ե� ��üũ��)
    AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, WindowRC.right - WindowRC.left,
        WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);

    // ������ ������ â�� ������ٸ� ShowWindow �Լ��� �̿��ؼ� â�� �������� ��������
    // �����Ѵ�.
    ShowWindow(mhWnd, SW_SHOW);

    // Ŭ���̾�Ʈ ������ ������ �ٽ� �׸��� ��û���ִ� �Լ��̴�.
    // ó�� �����ó� Ư����Ȳ�� â�� ���ΰ�ħ �ؾ� �� ��� ����Ѵ�.
    UpdateWindow(mhWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // ������ â ����޼���
    case WM_DESTROY:
        mLoop = false;
        PostQuitMessage(0);
        break;
    default:
        // ������ ������ �޼��� ���� �ٸ� �޼����� �߻��� ��� �������� �⺻ ��������
        // ó���� �ǰ� ������ش�.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
