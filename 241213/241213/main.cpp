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

	Obj[0]->SetName("가나다");
	// 오브젝트 클래스로 선언되었지만 실제 보유하려는 것들은 플레이어, 몬스터
	// 이럴 경우 다운캐스팅을 사용
	// 다만 사용에 주의
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