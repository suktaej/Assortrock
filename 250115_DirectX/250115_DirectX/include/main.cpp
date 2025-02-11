#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //int Size = sizeof(Test);
    /*CObject* Obj = nullptr;
    CSharedPtr  ptr = Obj;
    CObject* Obj1 = ptr;*/ 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //메모리 할당과 메모리릭에 대한 디버그
    //릭 체크시 디버그에서만 가능
    
    //_CrtSetBreakAlloc(100);
    //100의 오류를 찾아가는 방식
    //호출스택을 확인
    //호출 스택에서 작성했던 함수를 역순으로 찾아서 탐색

    if (!CGameManager::GetInst()->Init(hInstance))
    {
        CGameManager::DestroyInst();
        return 0;
	}

    int Ret = CGameManager::GetInst()->Run();
    CGameManager::DestroyInst();

    return Ret;
}

