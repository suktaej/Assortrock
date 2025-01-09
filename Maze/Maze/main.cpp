#include "GameManager.h"

int main()
{
	if (!FGameManager::GetInst()->Init())
	{
		FGameManager::GetInst()->DestroyInst();
		return 0;
	}

	FGameManager::GetInst()->Run();
	FGameManager::GetInst()->DestroyInst();

	return 0;
}