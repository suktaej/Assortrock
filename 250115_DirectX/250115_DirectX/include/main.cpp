#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //�޸� �Ҵ�� �޸𸮸��� ���� �����
    //�� üũ�� ����׿����� ����
    _CrtSetBreakAlloc(100);
    //100�� ������ ã�ư��� ���
    //ȣ�⽺���� Ȯ��
    //ȣ�� ���ÿ��� �ۼ��ߴ� �Լ��� �������� ã�Ƽ� Ž��

    int* n = new int;

    if (!CGameManager::GetInst()->Init(hInstance))
    {
        CGameManager::DestroyInst();
        return 0;
	}

    int Ret = CGameManager::GetInst()->Run();
    CGameManager::DestroyInst();

    return 0;
}