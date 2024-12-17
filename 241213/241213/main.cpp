#include "Player.h"
#include "Monster.h"

int main(void)
{
	CObject* Obj[100] = {};
	Obj[0] = new CPlayer;
	Obj[1] = new CMonster;
	
	for (int i = 0;i < 100;i++)
	{
		Obj[i]->Init();
	}

	Obj[0]->SetName("������");
	// ������Ʈ Ŭ������ ����Ǿ����� ���� �����Ϸ��� �͵��� �÷��̾�, ����
	// �̷� ��� �ٿ�ĳ������ ���
	// �ٸ� ��뿡 ����
	CPlayer* Char = dynamic_cast<CPlayer*>(Obj[0]);

	if (nullptr != Char)
	{
		Char->SetCharaterInfo(50, 20, 200, 100);
		Char->SetJob(EJob::Fighter);
	}

	Obj[0]->Output();

	for (int i = 0;i < 100;i++)
	{
		if (Obj[i])
		{
			delete Obj[i];
		}
	}
	return 0;
}