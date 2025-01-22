#pragma once

#define DIRECTINPUT_VERSION 0x0800

#define DIK_MOUSELBUTTON 0xfc
#define DIK_MOUSERBUTTON 0xfd
#define DIK_MOUSEWHEEL 0xfe

#include "../GameInfo.h"
//directX ���� input
#include <dinput.h>
//���������� ��ũ �ʼ�
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
	//� Ű�� ����ϴ��� �޾ƿ��� ����
	unsigned char Key = 0;
	//����Ű ���� ����
	bool Down = false;
	bool Hold = false;
	bool Up = false;
};

//�Լ��� ���� ����ü
struct FBindFunction
{
	void* Obj = nullptr;
	//STL�� ��� ������ std::function<��ȯŸ��> �Լ���
	std::function<void()> Func;
};

//Ű ���� ����
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
//�� ���� �Է¹޴� Ű�� �ٸ��� ������
//���� ���� ������ ���ϴ� Ű�� ���
	friend class CScene;
private:
	CInput();
	~CInput();
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	//Dinput��ü�κ��� ���� ���ϴ� ����̽��� ������ �� ����
	//�Է¹ް��� �ϴ� ����̽��� ��ü�� ���� 
	//�ش� ����̽��κ��� �Էµ� �� �ִ��� ������ ����
	IDirectInput8* m_Input = nullptr;
	IDirectInputDevice8* m_Keyboard = nullptr;
	IDirectInputDevice8* m_Mouse = nullptr;
	EInputSystem_Type m_InputType = EInputSystem_Type::DInput;

	std::unordered_map<unsigned char, FKeyState*> m_KeyStateMap;
	std::unordered_map<std::string, FBindKey*> m_BindKeyMap;

	//Ű���� �Է� ����
	unsigned char m_KeyState[256] = {};
	//DX���� �����ϴ� ���콺 ����
	//x,y: ���콺 ��ġ,z:�� ��, 0:����, 1:������, 2:��(Ŭ��)
	DIMOUSESTATE m_MouseState = {};
	//����Ű ���� 
	bool m_Ctrl = false;
	bool m_Alt = false;
	bool m_Shift = false;
	//���콺 ����
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
	//directX �ʱ�ȭ �� HINSTANCE �ʿ�
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
		//Ŭ���� �ɹ��Լ� ��� �� std::bind ���
		//�Լ��ּҿ� ��ü�� �̿��� func��ü�� ����
		BindFunc.Func = std::bind(Func, Object);

		BindKey->FunctionList[static_cast<int>(Type)].emplace_back(BindFunc);
	}
};
