#include "Player.h"
#include "Bash.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& Obj)	:
	CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	std::cout << "CPlayer Init" << std::endl;

	mSkillArray[0] = new CBash;

	mSkillArray[0]->Init();

    return true;
}

void CPlayer::Output()
{
	CCharacter::Output();
	std::cout << "직업 : " << (int)mJob <<
		std::endl;

	/*mMP -= mSkillArray[0]->GetMP();

	int Attack = mAttack + mSkillArray[0]->GetAtack();*/
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}
