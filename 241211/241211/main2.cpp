#include "GameManager.h"

int main(void)
{
	if (false == CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		//�ʱ�ȭ ���� �� �޸� ����
		return 0;
	}
	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();
	//���� ���� �� �޸� ����
	return 0;
}