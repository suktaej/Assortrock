#pragma once

#define DIRECTINPUT_VERSION 0x0800

#define DIK_MOUSELBUTTON 0xfc
#define DIK_MOUSERBUTTON 0xfd
#define DIK_MOUSEWHEEL 0xfe

#include "../GameInfo.h"
//directX 지원 input
#include <dinput.h>
//라이프러리 링크 필수
#pragma comment(lib,"dinput8.lib")

enum class EInputSystem_Type
{
	DInput,
	Window
};

enum class EMouse
{
	LButton,
	RButton,
	MButton,
	End
};

enum class EInputType
{
	Down,
	Hold,
	Up,
	End
};

struct FKeyState
{
	//어떤 키를 사용하는지 받아오는 변수
	unsigned char Key = 0;
	//조합키 여부 저장
	bool Down = false;
	bool Hold = false;
	bool Up = false;
};

//함수를 묶는 구조체
struct FBindFunction
{
	void* Obj = nullptr;
	//STL의 펑션 포인터 std::function<반환타입> 함수명
	std::function<void()> Func;
};

//키 조합 세팅
struct FBindKey
{
	FKeyState* Key = nullptr;
	bool Ctrl = false;
	bool Alt = false;
	bool Shift = false;

	std::vector<FBindFunction> FunctionList[static_cast<int>(EInputType::End)];
};

class CInput
{
//씬 마다 입력받는 키가 다르기 때문에
//씬이 열릴 때마다 원하는 키를 등록
	friend class CScene;
private:
	CInput();
	~CInput();
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	//Dinput객체로부터 내가 원하는 디바이스를 생성할 수 있음
	//입력받고자 하는 디바이스를 객체를 통해 
	//해당 디바이스로부터 입력된 게 있는지 정보를 얻어옴
	IDirectInput8* m_Input = nullptr;
	IDirectInputDevice8* m_Keyboard = nullptr;
	IDirectInputDevice8* m_Mouse = nullptr;
	EInputSystem_Type m_InputType = EInputSystem_Type::DInput;

	std::unordered_map<unsigned char, FKeyState*> m_KeyStateMap;
	std::unordered_map<std::string, FBindKey*> m_BindKeyMap;

	//키보드 입력 상태
	unsigned char m_KeyState[256] = {};
	//DX에서 지원하는 마우스 상태
	//x,y: 마우스 위치,z:휠 값, 0:왼쪽, 1:오른쪽, 2:휠(클릭)
	DIMOUSESTATE m_MouseState = {};
	//조합키 상태 
	bool m_Ctrl = false;
	bool m_Alt = false;
	bool m_Shift = false;
	//마우스 상태
	bool m_MouseDown[(int)EMouse::End] = {};
	bool m_MouseHold[(int)EMouse::End] = {};
	bool m_MouseUp[(int)EMouse::End] = {};
public:
	bool GetMouseDown(EMouse Type) { return m_MouseDown[(int)Type]; }
	bool GetMouseHold(EMouse Type) { return m_MouseHold[(int)Type]; }
	bool GetMouseUp(EMouse Type) { return m_MouseUp[(int)Type]; }
private:
	bool InitInput();
	bool UpdateKeyboard();
	bool UpdateMouse();

	void UpdateInput(float DeltaTime);
	void UpdateBind(float DeltaTime);

	FKeyState* FindKeyState(unsigned char Key);
	FBindKey* FindBindKey(const std::string& Name);

	unsigned char ConvertKey(unsigned char Key);
public:
	//directX 초기화 시 HINSTANCE 필요
	bool Init();
	void Update(float DeltaTime);

	void AddBindKey(const std::string& Name, unsigned char Key);
	void ChangeKeyCtrl(const std::string& Name, bool Ctrl);
	void ChangeKeyAlt(const std::string& Name, bool Alt);
	void ChangeKeyShift(const std::string& Name, bool Shift);
public:
	//class CInput* GetInput() const { return m_Input; }
public:
	template<typename T>
	void AddBindFunc(
		const std::string& KeyName, 
		EInputType Type, 
		T* Object, 
		void(T::*Func)())
	{
		FBindKey* BindKey = FindBindKey(KeyName);

		if (!BindKey)
			return;

		FBindFunction BindFunc;

		BindFunc.Obj = Object;
		//클래스 맴버함수 사용 시 std::bind 사용
		//함수주소와 객체를 이용해 func객체를 생성
		BindFunc.Func = std::bind(Func, Object);

		BindKey->FunctionList[static_cast<int>(Type)].emplace_back(BindFunc);
	}
};
