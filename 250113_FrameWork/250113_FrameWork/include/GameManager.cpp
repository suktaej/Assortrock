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
	//lstrcpy(m_ClassName, TEXT(""));	유니코드 텍스트 매크로
	lstrcpy(m_ClassName, L"FrameWork");
	lstrcpy(m_TitleName, L"FrameWork");

	RegisterWindowClass();
    
    if (!Create())
        return false;

    //인자로 들어간 윈도우에 출력할 수 있는 DC가 생성
    //GetDC로 얻어온 인자는 소멸자에서 ReleaseDC 실행
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
    FVector2D PlayerDir;
    //키입력 처리 함수
    //& 연산으로 0x8000이 true일 경우 누르고 있는 상태
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

    //PlayerDir(Vector2D)의 단위벡터화
    //방향이동시 모든 값이 일정하게 변화
    //단위벡터화 하지 않을 경우 시간당 거리를 이동
    //대각선 이동의 경우 약 1.4배 빠른 속도를 가짐
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
        //바라보는 방향을 향해 각도를 회전해서 발사하는 것이 일반
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
    //특수키는 Virtual key(VK_UP, VK_END)로 처리
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
        //생성
        (*iter1).Pos += Move;
        
        //삭제
        //벡터의 길이를 Dist에 업데이트
        float Dist = Move.Length();
        //객체의 사거리(Distance)를 이동한 거리만큼 감소
        (*iter1).Distance -= Dist;
        //사거리가 0이 될 경우 객체를 제거
        if ((*iter1).Distance <= 0.f)
        {
            iter1 = m_EnemyBulletList.erase(iter1);
            iter1End = m_EnemyBulletList.end();
            continue;
        }
        
        //탄환이 화면 외곽좌표에 도달하면 객체를 제거
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
