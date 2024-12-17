
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "GameManager.h"

int main()
{
	CGameManager::GetInst()->Init();

	CGameManager::DestroyInst();

	/*CObject* Obj = new CObject;

	delete Obj;*/
	/*CCharacter* Char = new CCharacter;

	delete Char;*/
	/*CPlayer* Player = new CPlayer;

	delete Player;*/

	//CObject* Array[10] = {};

	//Array[0] = new CPlayer;
	//Array[1] = new CMonster;
	//Array[2] = new CMonster;
	//Array[3] = new CItem;
	//Array[4] = Array[3]->Clone();

	////((CPlayer*)Array[0])->Init();
	////((CPlayer*)Array[0])->Init(10);

	//CObject1* Test = new CMonster;

	//delete Array[0];
	//delete Array[1];
	//delete Array[2];
	//delete Array[3];
	//delete Array[4];
	//delete Test;

	return 0;
}