#include "GameManager.h"

int main()
{
	srand(time(0));
	rand();

	if (!FGameManager::GetInst()->Init())
	{
		FGameManager::DestroyInst();
		return 0;
	}

	FGameManager::GetInst()->Run();
	FGameManager::DestroyInst();

	return 0;
}
