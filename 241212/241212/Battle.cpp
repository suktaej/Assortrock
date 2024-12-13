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
		std::cout << "1.����" << std::endl;
		std::cout << "2.����" << std::endl;
		std::cout << "�޴� ����: ";
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
			std::cout << "�÷��̾� �й�" << std::endl;
			Player->Resurrection();
			SAFE_DELETE(Monster);
			Monster = CObjectManager::GetInst()->CreateMonster(mType);
			system("pause");
			return;
		case EBattleResult::MonsterDeath:
			std::cout << "�÷��̾� �¸�" << std::endl;
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
	// �÷��̾� ����
	int	Damage = Player->GetATK() - Monster->GetDEF();

	// ���׿����� : ���ǽ� ? true�϶� : false�϶�
	Damage = Damage < 1 ? 1 : Damage;

	std::cout << Monster->GetName() << " ���� " <<
		Damage << " ���ظ� �������ϴ�." << std::endl;

	Monster->SetHP(Monster->GetHP() - Damage);

	if (Monster->GetHP() <= 0)
		return EBattleResult::MonsterDeath;

	// ���� ����
	Damage = Monster->GetATK() - Player->GetDEF();
	Damage = Damage < 1 ? 1 : Damage;

	Player->SetHP(Player->GetHP() - Damage);

	std::cout << Monster->GetName() << " ���� " <<
		Damage << " ���ظ� �Ծ����ϴ�." << std::endl;

	if (Player->GetHP() <= 0)
		return EBattleResult::PlayerDeath;

	return EBattleResult::None;
}
