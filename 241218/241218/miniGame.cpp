#include "GameManager.h"

int main(void)
{
//	COORD Pos;
//	Pos.X = 5;
//	Pos.Y = 3;
//
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
	//�ܼ�â���� ��ǥ�� �����Ͽ� �ش���ǥ�� ����� �� �� �ְ� ������ִ� �Լ�
	//�ܼ�â�� ���Ŀ���� ����
	//��� Ŀ���� ��ġ�� �����ϴ� �Լ�

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
