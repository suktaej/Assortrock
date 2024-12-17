#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "GameManager.h"

int main()
{
	CGameManager::GetInst()->Init();
	CGameManager::DestroyInst();
	return 0;
}

