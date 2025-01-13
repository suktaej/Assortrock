#include "GameManager.h"
#include "resource.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
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
    //Ű�Է� ó�� �Լ�
    //& �������� 0x8000�� true�� ��� ������ �ִ� ����
    if (GetAsyncKeyState('W') & 0x8000)
    {
        m_RC.Top -= 400*DeltaTime;
        m_RC.Bottom -= 400 * DeltaTime;
    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        m_RC.Top += 400*DeltaTime;
        m_RC.Bottom += 400 * DeltaTime;
    }
    
    if (GetAsyncKeyState('D') & 0x8000)
    {
        m_RC.Right += 400*DeltaTime;
        m_RC.Left += 400 * DeltaTime;
    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        m_RC.Right -= 400*DeltaTime;
        m_RC.Left -= 400 * DeltaTime;
    }
    //Ư��Ű�� Virtual key(VK_UP, VK_END)�� ó��
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        FRect Bullet;

        Bullet.Left = m_RC.Left + 100.f;
        Bullet.Top = m_RC.Top + 25.f;
        Bullet.Right = Bullet.Left + 50.f;
        Bullet.Bottom = Bullet.Top + 50.f;

        m_BulletList.push_back(Bullet);
    }
}

void CGameManager::Update(float DeltaTime)
{
    std::list<FRect>::iterator iter = m_BulletList.begin();
    std::list<FRect>::iterator iterEnd = m_BulletList.end();

    while (iter != iterEnd)
    {
        (*iter).Left += 500.f * DeltaTime;
        (*iter).Right += 500.f * DeltaTime;
        iter++;
    }

    m_EnemyBulletCreate += DeltaTime;

    if (m_EnemyBulletCreate >= 1.f)
    {
        FRect Bullet;

        Bullet.Left = m_Enemy.Left - 50.f;
        Bullet.Top = m_Enemy.Top + 25.f;
        Bullet.Right = Bullet.Left + 50.f;
        Bullet.Bottom = Bullet.Top + 50.f;

        m_EnemyBulletList.push_back(Bullet);

        m_EnemyBulletCreate -= 1;
    }

	std::list<FRect>::iterator iter1 = m_EnemyBulletList.begin();
	std::list<FRect>::iterator iter1End = m_EnemyBulletList.end();
    
    while (iter1 != iter1End)
    {
        (*iter1).Left -= 500.f * DeltaTime;
        (*iter1).Right -= 500.f * DeltaTime;
        iter1++;
    }

    if (m_bEnemyMove)
    {
        m_Enemy.Top += 300.f * DeltaTime;
        m_Enemy.Bottom += 300.f * DeltaTime;
        if (m_Enemy.Bottom >= 719)
            m_bEnemyMove = false;
    }
    else
    {
        m_Enemy.Top -= 300.f * DeltaTime;
        m_Enemy.Bottom -= 300.f * DeltaTime;
        if (m_Enemy.Top <= 1)
            m_bEnemyMove = true;
    }
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
    //Rectangle(m_hdc, 1, 1, 1279, 719);
    Rectangle(m_hdc, m_RC.Left, m_RC.Top, m_RC.Right, m_RC.Bottom);
    Rectangle(m_hdc, m_Enemy.Left, m_Enemy.Top, m_Enemy.Right, m_Enemy.Bottom);
    
    std::list<FRect>::iterator iter = m_BulletList.begin();
    std::list<FRect>::iterator iterEnd = m_BulletList.end();
   
    while (iter != iterEnd)
    {
        Ellipse(m_hdc, (*iter).Left, (*iter).Top, (*iter).Right, (*iter).Bottom);
        iter++;
    }

    std::list<FRect>::iterator iter1 = m_EnemyBulletList.begin();
    std::list<FRect>::iterator iter1End = m_EnemyBulletList.end();

    while (iter1 != iter1End)
    {
        Ellipse(m_hdc, (*iter1).Left, (*iter1).Top, (*iter1).Right, (*iter1).Bottom);
        iter1++;
    }
}
