#include "Input.h"
#include "../GameManager.h"
#include "../Device.h"


CInput::CInput()
{
}

CInput::~CInput()
{
    auto iter = m_KeyStateMap.begin();
    auto iterEnd = m_KeyStateMap.end();

    while (iter != iterEnd)
    {
        SAFE_DELETE(iter->second);
        iter++;
    }

    auto	iter1 = m_BindKeyMap.begin();
    auto	iter1End = m_BindKeyMap.end();

    while(iter1!=iter1End)
    {
        SAFE_DELETE(iter1->second);
        iter++;
    }

	if (m_Keyboard)
	{
		m_Keyboard->Unacquire();
		SAFE_RELEASE(m_Keyboard);
	}

	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		SAFE_RELEASE(m_Mouse);
	}
	
	SAFE_RELEASE(m_Input);
}

bool CInput::Init()
{
	m_hInst = CGameManager::GetInst()->GetWindowInstance();
	m_hWnd = CGameManager::GetInst()->GetWindowHandle();

	if (FAILED(DirectInput8Create(
		m_hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_Input,
		nullptr)))
	{
		m_InputType = EInputSystem_Type::Window;
	}

	if (m_InputType == EInputSystem_Type::DInput)
	{
		if (!InitInput())
			return false;
	}
	return true;
}

bool CInput::InitInput()
{
	//키보드 장치 생성
	if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_Keyboard, nullptr)))
		return false;
	//입력장치가 생성되었다면 데이터 형식 설정
	if (FAILED(m_Keyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;

	if(CDevice::GetInst()->GetWindowMode())
	{ 
		//수준 설정
		//foreground: 활성화 시에만 키를 입력받음(풀스크린 시 주로 사용)
		//background: 백그라운드에서도 사용가능
		// 활성 상태가 아니어도 키 입력이 가능
		//exclusive : 입력 디바이스를 독점모드로 설정(풀스크린 시 주로 사용)
		//nonexclusive: 입력 디바이스를 비독점 모드로 설정 
		if (FAILED(m_Keyboard->SetCooperativeLevel(
			m_hWnd,
			//윈도우 창일 경우
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
			return false;
	}
	else
	{	
		if (FAILED(m_Keyboard->SetCooperativeLevel(
			m_hWnd,
			//풀스크린일 경우
			DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
			return false;
	}
	//키보드 장치 획득
	if (FAILED(m_Keyboard->Acquire()))
		return false;

	//마우스
	if (FAILED(m_Input->CreateDevice(GUID_SysMouse, &m_Mouse, nullptr)))
		return false;
	if (FAILED(m_Mouse->SetDataFormat(&c_dfDIMouse)))
		return false;

	if (CDevice::GetInst()->GetWindowMode())
	{
		if (FAILED(m_Mouse->SetCooperativeLevel(
			m_hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
			return false;
	}
	else
	{
		if (FAILED(m_Mouse->SetCooperativeLevel(
			m_hWnd,
			DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
			return false;
	}
	if (FAILED(m_Mouse->Acquire()))
		return false;

	return true;
}

void CInput::Update(float DeltaTime)
{
	if (m_InputType == EInputSystem_Type::DInput)
	{
		UpdateKeyboard();
		UpdateMouse();
	}
	UpdateInput(DeltaTime);
    UpdateBind(DeltaTime);
}


bool CInput::UpdateKeyboard()
{
	//장치가 없으면 종료
	if (!m_Keyboard)
		return false;
	//인자 1 :사이즈, 인자 2: (LPVOID)상태
	HRESULT result = m_Keyboard->GetDeviceState(sizeof(m_KeyState),(LPVOID)&m_KeyState);
	
	//결과를 받아오는데 실패 시
	if(FAILED(result))
	{
		//재요청
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_Keyboard->Acquire();
	}

	return true;
}

bool CInput::UpdateMouse()
{
	if (!m_Mouse)
		return false;

	HRESULT result = m_Mouse->GetDeviceState(sizeof(m_MouseState),(LPVOID)&m_MouseState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_Mouse->Acquire();
	}

	return true;
}

void CInput::UpdateInput(float DeltaTime)
{
	switch (m_InputType)
	{
	case EInputSystem_Type::DInput:
		if (m_KeyState[DIK_LCONTROL] & 0x80)
			m_Ctrl = true;
		else
			m_Ctrl = false;

		if (m_KeyState[DIK_LSHIFT] & 0x80)
			m_Shift = true;
		else
			m_Shift = false;

		if (m_KeyState[DIK_LALT] & 0x80)
			m_Alt = true;
		else
			m_Alt = false;

		for (int i = 0; i<static_cast<int>(EMouse::End);i++)
		{
			if (m_MouseState.rgbButtons[i] & 0x80)
			{
				//Down이 false인 경우는 처음 누르는 경우
				if (!m_MouseDown[i] && !m_MouseHold[i])
				{
					m_MouseDown[i] = true;
					m_MouseHold[i] = true;
				}
				//이전 프레임에도 누르고 유지하는 중
				else
				{
					m_MouseDown[i] = false;
				}
			}
			//키는 누르지 않았지만 hold가 true라면 뗀 상태
			else if (m_MouseHold[i])
			{
				m_MouseDown[i] = false;
				m_MouseHold[i] = false;
				m_MouseUp[i] = true;
			}
			else if (m_MouseUp[i])
			{
				m_MouseUp[i] = false;
			}
		}
		break;
	case EInputSystem_Type::Window:
		break;
	}
    auto	iter = m_KeyStateMap.begin();
    auto	iterEnd = m_KeyStateMap.end();

    for (; iter != iterEnd; ++iter)
    {
        bool	KeyPush = false;

        switch (iter->second->Key)
        {
        case DIK_MOUSELBUTTON:
            if (m_MouseState.rgbButtons[(int)EMouse::LButton] & 0x80)
                KeyPush = true;
            break;
        case DIK_MOUSERBUTTON:
            if (m_MouseState.rgbButtons[(int)EMouse::RButton] & 0x80)
                KeyPush = true;
            break;
        case DIK_MOUSEWHEEL:
            break;
        default:
            if (m_KeyState[iter->second->Key] & 0x80)
                KeyPush = true;
            break;
        }

        // 현재 해당 키를 누르고 있을 경우
        if (KeyPush)
        {
            //이제 막 버튼을 누름
            if (!iter->second->Down && !iter->second->Hold)
            {
                iter->second->Down = true;
                iter->second->Hold = true;
            }
            //버튼을 누르는 상태(Hold = true)
            else
                iter->second->Down = false;
        }
        // 현재 해당 키를 안누르고 있을 경우
        // Hold가 true라면 이전프레임에 이 키를 누르고 있다가
        // 이제 막 키를 해제
        else if (iter->second->Hold)
        {
            iter->second->Down = false;
            iter->second->Hold = false;
            iter->second->Up = true;
        }
        else if (iter->second->Up)
            iter->second->Up = false;
    }
}

void CInput::UpdateBind(float DeltaTime)
{
    auto iter = m_BindKeyMap.begin();
    auto iterEnd = m_BindKeyMap.end();

    while (iter != iterEnd)
    {
        //down이 충족 될 경우 등록한 함수 호출
        if (iter->second->Key->Down &&
            iter->second->Ctrl == m_Ctrl &&
            iter->second->Alt == m_Alt &&
            iter->second->Shift == m_Shift)
        {
            size_t Size = iter->second->FunctionList[(int)EInputType::Down].size();

            for (size_t i = 0;i < Size;i++)
                iter->second->FunctionList[(int)EInputType::Down][i].Func(DeltaTime);
        }
        if (iter->second->Key->Hold &&
            iter->second->Ctrl == m_Ctrl &&
            iter->second->Alt == m_Alt &&
            iter->second->Shift == m_Shift)
        {
            size_t Size = iter->second->FunctionList[(int)EInputType::Hold].size();

            for (size_t i = 0;i < Size;i++)
                iter->second->FunctionList[(int)EInputType::Hold][i].Func(DeltaTime);
        }
        if (iter->second->Key->Up &&
            iter->second->Ctrl == m_Ctrl &&
            iter->second->Alt == m_Alt &&
            iter->second->Shift == m_Shift)
        {
            size_t Size = iter->second->FunctionList[(int)EInputType::Up].size();

            for (size_t i = 0;i < Size;i++)
                iter->second->FunctionList[(int)EInputType::Up][i].Func(DeltaTime);
        }
        iter++;
    }
}

FKeyState* CInput::FindKeyState(unsigned char Key)
{
    auto iter = m_KeyStateMap.find(Key);

    if (iter == m_KeyStateMap.end())
        return nullptr;

    return iter->second;
}

FBindKey* CInput::FindBindKey(const std::string& Name)
{
	auto iter = m_BindKeyMap.find(Name);
	if (iter == m_BindKeyMap.end())
		return nullptr;

	return iter->second;
}


void CInput::AddBindKey(const std::string& Name, unsigned char Key)
{   
    //중복된 이름이 있는지 판단
	if (FindBindKey(Name))
		return;

	FBindKey* NewKey = new FBindKey;
	FKeyState* State = FindKeyState(Key);

    //키가 없다면 생성 후 등록
    if (!State)
    {
        State = new FKeyState;
        State->Key = ConvertKey(Key);
        m_KeyStateMap.insert(std::make_pair(Key, State));
    }

    NewKey->Key = State;
    m_BindKeyMap.insert(std::make_pair(Name, NewKey));
}

void CInput::ChangeKeyCtrl(const std::string& Name, bool Ctrl)
{
    FBindKey* Key = FindBindKey(Name);

    if (!Key)
        return;

    Key->Ctrl = Ctrl;
}

void CInput::ChangeKeyAlt(const std::string& Name, bool Alt)
{
    FBindKey* Key = FindBindKey(Name);

    if (!Key)
        return;

    Key->Alt = Alt;
}

void CInput::ChangeKeyShift(const std::string& Name, bool Shift)
{
    FBindKey* Key = FindBindKey(Name);

    if (!Key)
        return;

    Key->Shift = Shift;
}

unsigned char CInput::ConvertKey(unsigned char Key)
{
    if (m_InputType == EInputSystem_Type::DInput)
    {
        switch (Key)
        {
        case VK_LBUTTON:
            return DIK_MOUSELBUTTON;
        case VK_RBUTTON:
            return DIK_MOUSERBUTTON;
        case VK_MBUTTON:
            return DIK_MOUSEWHEEL;
        case VK_BACK:
            return DIK_BACK;
        case VK_TAB:
            return DIK_TAB;
        case VK_RETURN:
            return DIK_RETURN;
        case VK_LCONTROL:
            return DIK_LCONTROL;
        case VK_RCONTROL:
            return DIK_RCONTROL;
        case VK_LMENU:
            return DIK_LALT;
        case VK_RMENU:
            return DIK_RALT;
        case VK_LSHIFT:
            return DIK_LSHIFT;
        case VK_RSHIFT:
            return DIK_RSHIFT;
        case VK_PAUSE:
            return DIK_PAUSE;
        case VK_CAPITAL:
            return DIK_CAPSLOCK;
        case VK_ESCAPE:
            return DIK_ESCAPE;
        case VK_SPACE:
            return DIK_SPACE;
        case VK_NEXT:
            return DIK_PGDN;
        case VK_PRIOR:
            return DIK_PGUP;
        case VK_END:
            return DIK_END;
        case VK_HOME:
            return DIK_HOME;
        case VK_LEFT:
            return DIK_LEFT;
        case VK_UP:
            return DIK_UP;
        case VK_RIGHT:
            return DIK_RIGHT;
        case VK_DOWN:
            return DIK_DOWN;
        case VK_PRINT:
            return DIK_SYSRQ;
        case VK_INSERT:
            return DIK_INSERT;
        case VK_DELETE:
            return DIK_DELETE;
        case VK_HELP:
            return 0;
        case '0':
            return DIK_0;
        case '1':
            return DIK_1;
        case '2':
            return DIK_2;
        case '3':
            return DIK_3;
        case '4':
            return DIK_4;
        case '5':
            return DIK_5;
        case '6':
            return DIK_6;
        case '7':
            return DIK_7;
        case '8':
            return DIK_8;
        case '9':
            return DIK_9;
        case 'A':
            return DIK_A;
        case 'B':
            return DIK_B;
        case 'C':
            return DIK_C;
        case 'D':
            return DIK_D;
        case 'E':
            return DIK_E;
        case 'F':
            return DIK_F;
        case 'G':
            return DIK_G;
        case 'H':
            return DIK_H;
        case 'I':
            return DIK_I;
        case 'J':
            return DIK_J;
        case 'K':
            return DIK_K;
        case 'L':
            return DIK_L;
        case 'M':
            return DIK_M;
        case 'N':
            return DIK_N;
        case 'O':
            return DIK_O;
        case 'P':
            return DIK_P;
        case 'Q':
            return DIK_Q;
        case 'R':
            return DIK_R;
        case 'S':
            return DIK_S;
        case 'T':
            return DIK_T;
        case 'U':
            return DIK_U;
        case 'V':
            return DIK_V;
        case 'W':
            return DIK_W;
        case 'X':
            return DIK_X;
        case 'Y':
            return DIK_Y;
        case 'Z':
            return DIK_Z;
        case VK_OEM_3:
            return DIK_GRAVE;
        case VK_OEM_MINUS:
            return DIK_MINUS;
        case VK_OEM_NEC_EQUAL:
            return DIK_EQUALS;
        case VK_OEM_4:
            return DIK_LBRACKET;
        case VK_OEM_6:
            return DIK_RBRACKET;
        case VK_OEM_5:
            return DIK_BACKSLASH;
        case VK_OEM_1:
            return DIK_SEMICOLON;
        case VK_OEM_7:
            return DIK_APOSTROPHE;
        case VK_OEM_COMMA:
            return DIK_COMMA;
        case VK_OEM_PERIOD:
            return DIK_PERIOD;
        case VK_OEM_2:
            return DIK_SLASH;
        case VK_NUMPAD0:
            return DIK_NUMPAD0;
        case VK_NUMPAD1:
            return DIK_NUMPAD1;
        case VK_NUMPAD2:
            return DIK_NUMPAD2;
        case VK_NUMPAD3:
            return DIK_NUMPAD3;
        case VK_NUMPAD4:
            return DIK_NUMPAD4;
        case VK_NUMPAD5:
            return DIK_NUMPAD5;
        case VK_NUMPAD6:
            return DIK_NUMPAD6;
        case VK_NUMPAD7:
            return DIK_NUMPAD7;
        case VK_NUMPAD8:
            return DIK_NUMPAD8;
        case VK_NUMPAD9:
            return DIK_NUMPAD9;
        case VK_MULTIPLY:
            return DIK_MULTIPLY;
        case VK_ADD:
            return DIK_ADD;
        case VK_SEPARATOR:
            return DIK_NUMPADCOMMA;
        case VK_SUBTRACT:
            return DIK_SUBTRACT;
        case VK_DECIMAL:
            return DIK_DECIMAL;
        case VK_DIVIDE:
            return DIK_DIVIDE;
            //case VK_RETURN:      
            //return DIK_NUMPADENTER;
        case VK_F1:
            return DIK_F1;
        case VK_F2:
            return DIK_F2;
        case VK_F3:
            return DIK_F3;
        case VK_F4:
            return DIK_F4;
        case VK_F5:
            return DIK_F5;
        case VK_F6:
            return DIK_F6;
        case VK_F7:
            return DIK_F7;
        case VK_F8:
            return DIK_F8;
        case VK_F9:
            return DIK_F9;
        case VK_F10:
            return DIK_F10;
        case VK_F11:
            return DIK_F11;
        case VK_F12:
            return DIK_F12;
        case VK_F13:
            return DIK_F13;
        case VK_F14:
            return DIK_F14;
        case VK_F15:
            return DIK_F15;
        case VK_F16:
        case VK_F17:
        case VK_F18:
        case VK_F19:
        case VK_F20:
        case VK_F21:
        case VK_F22:
        case VK_F23:
        case VK_F24:
            return 0;
        case VK_NUMLOCK:
            return DIK_NUMLOCK;
        case VK_SCROLL:
            return DIK_SCROLL;
        case VK_LWIN:
            return DIK_LWIN;
        case VK_RWIN:
            return DIK_RWIN;
        case VK_APPS:
            return DIK_APPS;
        case VK_OEM_102:
            return DIK_OEM_102;
        }
        return 0xff;
    }
    return Key;
}
