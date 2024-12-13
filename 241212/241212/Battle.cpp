#include "Battle.h"

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

void CBattle::Run()
{
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();
	CMonster* Monster = CObjectManager::GetInst()->CreateMonster(mType);
	while (true)
	{
		system("cls");
		Player->Output();
		Monster->Output();
		
		std::cout << "---------------" << std::endl;
		std::cout << "1.전투" << std::endl;
		std::cout << "2.도주" << std::endl;
		std::cout << "메뉴 선택: ";
		int Input;
		std::cin >> Input;

		if (Input <= (int)EBattleSelect::None ||
			Input > (int)EBattleSelect::Escape)
			continue;
		else if (Input == (int)EBattleSelect::Escape)
		{
			SAFE_DELETE(Monster);
			break;
		}

		switch (Fight(Player, Monster))
		{
		case EBattleResult::PlayerDeath:
			std::cout << "플레이어 패배" << std::endl;
			Player->Resurrection();
			SAFE_DELETE(Monster);
			Monster = CObjectManager::GetInst()->CreateMonster(mType);
			system("pause");
			return;
		case EBattleResult::MonsterDeath:
			std::cout << "플레이어 승리" << std::endl;
			Player->SetResult(Monster->GetEXP(), Monster->GetGold());
			SAFE_DELETE(Monster);
			Monster = CObjectManager::GetInst()->CreateMonster(mType);
			break;
		}
		system("pause");

	}
}


void CBattle::SetBattleType(EBattleType Type)
{
	mType = Type;
}

EBattleResult CBattle::Fight(CPlayer* Player, CMonster* Monster)
{
	// 플레이어 공격
	int	Damage = Player->GetATK() - Monster->GetDEF();

	// 삼항연산자 : 조건식 ? true일때 : false일때
	Damage = Damage < 1 ? 1 : Damage;

	std::cout << Monster->GetName() << " 에게 " <<
		Damage << " 피해를 입혔습니다." << std::endl;

	Monster->SetHP(Monster->GetHP() - Damage);

	if (Monster->GetHP() <= 0)
		return EBattleResult::MonsterDeath;

	// 몬스터 공격
	Damage = Monster->GetATK() - Player->GetDEF();
	Damage = Damage < 1 ? 1 : Damage;

	Player->SetHP(Player->GetHP() - Damage);

	std::cout << Monster->GetName() << " 에게 " <<
		Damage << " 피해를 입었습니다." << std::endl;

	if (Player->GetHP() <= 0)
		return EBattleResult::PlayerDeath;

	return EBattleResult::None;
}
