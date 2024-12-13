#include "GameManager.h"

int main(void)
{
	if (false == CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		//초기화 실패 시 메모리 제거
		return 0;
	}
	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();
	//게임 종료 시 메모리 제거
	return 0;
}