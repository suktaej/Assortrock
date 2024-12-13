#include "GameManager.h"

int main()
{
	if (false == CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();
	CGameManager::DestroyInst();
	return 0;
}

//inventory class 생성
//inventory class는 singleton
//최대 10개까지 저장
//구매 시 돈을 차감
//아이템을 복제(복사생성자)하여 인벤토리 추가
