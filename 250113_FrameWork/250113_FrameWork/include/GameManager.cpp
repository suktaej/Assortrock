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
    FVector2D PlayerDir;
    //Ű�Է� ó�� �Լ�
    //& �������� 0x8000�� true�� ��� ������ �ִ� ����
    if (GetAsyncKeyState('W') & 0x8000)
    {
        PlayerDir.y -= 1.f;
        //m_RC.Top -= 400*DeltaTime;
        //m_RC.Bottom -= 400 * DeltaTime;
    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        PlayerDir.y += 1.f;
        //m_RC.Top += 400*DeltaTime;
        //m_RC.Bottom += 400 * DeltaTime;
    }
    
    if (GetAsyncKeyState('D') & 0x8000)
    {
        PlayerDir.x += 1.f;
        //m_RC.Right += 400*DeltaTime;
        //m_RC.Left += 400 * DeltaTime;
    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        PlayerDir.x -= 1.f;
        //m_RC.Right -= 400*DeltaTime;
        //m_RC.Left -= 400 * DeltaTime;
    }

    //PlayerDir(Vector2D)�� ��������ȭ
    //�����̵��� ��� ���� �����ϰ� ��ȭ
    //��������ȭ ���� ���� ��� �ð��� �Ÿ��� �̵�
    //�밢�� �̵��� ��� �� 1.4�� ���� �ӵ��� ����
    PlayerDir.Normalize();
    m_PlayerPos += PlayerDir * 400.f * DeltaTime;

    if (GetAsyncKeyState('1') & 0x8000)
    {   
        for (int i = 0; i < 3;i++)
        {
            FBullet Bullet;

            Bullet.Pos.x = m_PlayerPos.x + m_PlayerSize.x / 2.f + 25.f;
            Bullet.Pos.y = m_PlayerPos.y;
            Bullet.Size = FVector2D(50.f, 50.f);
            Bullet.MoveDir = FVector2D(1.f, i - 1.f);
            Bullet.MoveDir.Normalize();

            m_BulletList.push_back(Bullet);
        }
        //�ٶ󺸴� ������ ���� ������ ȸ���ؼ� �߻��ϴ� ���� �Ϲ�
    }

    if (GetAsyncKeyState('2') & 0x8000)
    {
        FVector2D Dir[8] =
        {
            {1.f, 0.f},
            {1.f, 1.f},
            {0.f, 1.f},
            {-1.f, 1.f},
            {-1.f, 0.f},
            {-1.f, -1.f},
            {0.f, -1.f},
            {1.f, -1.f}
        };

        for (int i = 0; i < 8;i++)
        {
            FBullet Bullet;

            //Bullet.Pos.x = m_PlayerPos.x + m_PlayerSize.x / 2.f + 25.f;
            //Bullet.Pos.y = m_PlayerPos.y;
            Bullet.Size = FVector2D(50.f, 50.f);
            Bullet.MoveDir = Dir[i];
            Bullet.MoveDir.Normalize();
            
            Bullet.Pos = m_PlayerPos + Bullet.MoveDir * 100.f;

            m_BulletList.push_back(Bullet);
        }
    }
    if (GetAsyncKeyState('3') & 0x8000)
    {
        FBullet Bullet;
        
        Bullet.Pos.x = m_PlayerPos.x + m_PlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = 300;//m_PlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDir = FVector2D(1.f, -1.f);
        Bullet.MoveDir.Normalize();

        Bullet.Distance = FLT_MAX;
        Bullet.Option = EBulletOption::Bound;

        m_BulletList.push_back(Bullet);
    }
    //Ư��Ű�� Virtual key(VK_UP, VK_END)�� ó��
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        FBullet Bullet;

        Bullet.Pos.x = m_PlayerPos.x + m_PlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = m_PlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDir = FVector2D(1.f, 0.f);
        Bullet.Distance = 1000.f;

        m_BulletList.push_back(Bullet);
    }
}

void CGameManager::Update(float DeltaTime)
{
    //Player bullet traversal
    std::list<FBullet>::iterator iter = m_BulletList.begin();
    std::list<FBullet>::iterator iterEnd = m_BulletList.end();
    
    while (iter != iterEnd)
    {
        FVector2D Move = (*iter).MoveDir * 500.f * DeltaTime;

        (*iter).Pos += Move;
       
        float Dist = Move.Length();
        (*iter).Distance -= Dist;
        
        if ((*iter).Distance <= 0.f)
        {
            iter = m_BulletList.erase(iter);
            iterEnd = m_BulletList.end();
            continue;
        }

        else if (((*iter).Pos.x + (*iter).Size.x / 2.f <= 0.f ||
            (*iter).Pos.y + (*iter).Size.y / 2.f <= 0.f ||
            (*iter).Pos.x - (*iter).Size.x / 2.f >= 1280.f ||
            (*iter).Pos.y - (*iter).Size.y / 2.f >= 720.f) &&
            (*iter).Option == EBulletOption::Normal)
        {
            iter = m_BulletList.erase(iter);
            iterEnd = m_BulletList.end();
            continue;
        }

        else if ((*iter).Option==EBulletOption::Bound)
        {
            FVector2D Normal;

            if ((*iter).Pos.x - (*iter).Size.x / 2.f <= 0.f)
            {
                Normal.x = 1.f;
                (*iter).Pos.x = 25.f;
            }
            else if ((*iter).Pos.x + (*iter).Size.x / 2.f >= 1280.f)
            {
                Normal.x = -1.f;
                (*iter).Pos.x = 1255.f;
            }
            else if ((*iter).Pos.y + (*iter).Size.y / 2.f <= 0.f)
            {
                Normal.y = 1.f;
                (*iter).Pos.y = 25.f;
            }
            else if ((*iter).Pos.y + (*iter).Size.y / 2.f >= 720.f)
            {
                Normal.y = -1.f;
                (*iter).Pos.y = 695.f;
            }
			
            if (Normal.Length() > 0.f)
            {
                (*iter).MoveDir = (*iter).MoveDir - Normal * 2.f * Normal.Dot((*iter).MoveDir);
                (*iter).MoveDir.Normalize();
            }
        }
        iter++;
    }

    //Enemy Movement 
    m_EnemyPos.y += m_EnemyDir * 300.f * DeltaTime;

    if (m_EnemyPos.y - m_EnemySize.y / 2.f >=720.f)
    {
        m_EnemyPos.y = 670.f;
        m_EnemyDir = -1.f;
    }
    else if (m_EnemyPos.y - m_EnemySize.y / 2.f <= 0.f)
    {
        m_EnemyPos.y = 50.f;
        m_EnemyDir = 1.f;
    }

    //Enemy Bullet traversal
	std::list<FBullet>::iterator iter1 = m_EnemyBulletList.begin();
	std::list<FBullet>::iterator iter1End = m_EnemyBulletList.end();
    
    while (iter1 != iter1End)
    {
        FVector2D Move = (*iter1).MoveDir * 500.f * DeltaTime;
        //����
        (*iter1).Pos += Move;
        
        //����
        //������ ���̸� Dist�� ������Ʈ
        float Dist = Move.Length();
        //��ü�� ��Ÿ�(Distance)�� �̵��� �Ÿ���ŭ ����
        (*iter1).Distance -= Dist;
        //��Ÿ��� 0�� �� ��� ��ü�� ����
        if ((*iter1).Distance <= 0.f)
        {
            iter1 = m_EnemyBulletList.erase(iter1);
            iter1End = m_EnemyBulletList.end();
            continue;
        }
        
        //źȯ�� ȭ�� �ܰ���ǥ�� �����ϸ� ��ü�� ����
		if ((*iter1).Pos.x + (*iter1).Size.x / 2.f <= 10.f ||
			(*iter1).Pos.y + (*iter1).Size.y / 2.f <= 10.f ||
			(*iter1).Pos.x - (*iter1).Size.x / 2.f >= 1270.f ||
			(*iter1).Pos.y - (*iter1).Size.y / 2.f >= 710.f)
        {
            iter1 = m_EnemyBulletList.erase(iter1);
            iter1End = m_EnemyBulletList.end();
            continue;
        }
        iter1++;
    }
    //Enemy Bullet Create

    m_FireAccTime += DeltaTime;

    if (m_FireAccTime >= m_FireTime)
    {
        m_FireAccTime -= m_FireTime;
        
        FBullet Bullet;

        Bullet.Pos.x = m_EnemyPos.x - m_EnemySize.x / 2.f - 25.f;
        Bullet.Pos.y = m_EnemyPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        //Vector minus
        Bullet.MoveDir = m_PlayerPos - Bullet.Pos;
        Bullet.MoveDir.Normalize();

        Bullet.Distance = 800.f;

        m_EnemyBulletList.push_back(Bullet);
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
    //Player
    Rectangle(m_hdc, 
        (int)(m_PlayerPos.x - m_PlayerSize.x / 2.f),
		(int)(m_PlayerPos.y - m_PlayerSize.y / 2.f),
		(int)(m_PlayerPos.x + m_PlayerSize.x / 2.f),
		(int)(m_PlayerPos.y + m_PlayerSize.y / 2.f));

    //PlayerBullet
    std::list<FBullet>::iterator iter = m_BulletList.begin();
    std::list<FBullet>::iterator iterEnd = m_BulletList.end();

    while (iter != iterEnd)
    {
        Ellipse(m_hdc,
            (int)((*iter).Pos.x - (*iter).Size.x/2.f),
            (int)((*iter).Pos.y - (*iter).Size.y/2.f),
            (int)((*iter).Pos.x + (*iter).Size.x/2.f),
            (int)((*iter).Pos.y + (*iter).Size.y/2.f));
        iter++;
    }
    
    //Enemy
    Rectangle(m_hdc, 
        (int)(m_EnemyPos.x - m_EnemySize.x / 2.f),
        (int)(m_EnemyPos.y - m_EnemySize.y / 2.f),
        (int)(m_EnemyPos.x + m_EnemySize.x / 2.f),
        (int)(m_EnemyPos.y + m_EnemySize.y / 2.f));

    //EnemyBullet
    std::list<FBullet>::iterator iter1 = m_EnemyBulletList.begin();
    std::list<FBullet>::iterator iter1End = m_EnemyBulletList.end();

    while (iter1 != iter1End)
    {
        Ellipse(m_hdc, 
            (int)((*iter1).Pos.x - (*iter1).Size.x/2.f),
            (int)((*iter1).Pos.y - (*iter1).Size.y/2.f),
            (int)((*iter1).Pos.x + (*iter1).Size.x/2.f),
            (int)((*iter1).Pos.y + (*iter1).Size.y/2.f));
        iter1++;
    }
}
