#include "GameInfo.h"
#include "GameManager.h"

int main()
{
	CGameManager::GetInst();
	CGameManager::DestroyInst();

	return 0;
}
