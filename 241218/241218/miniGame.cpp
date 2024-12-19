#include "GameManager.h"

int main(void)
{
//	COORD Pos;
//	Pos.X = 5;
//	Pos.Y = 3;
//
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
	//콘솔창에서 좌표를 지정하여 해당좌표에 출력을 할 수 있게 만들어주는 함수
	//콘솔창은 출력커서가 존재
	//출력 커서의 위치를 지정하는 함수

	std::cout << "*" << std::endl;

	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();
	CGameManager::DestroyInst();

	return 0;
}
