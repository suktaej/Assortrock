#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& Obj):CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	//skill ±¸Çö
	return true;
}

void CPlayer::Output()
{
	CCharacter::Output();
	switch (mJob)
	{
	case EJob::Fighter:
		std::cout << "Fighter" << std::endl;
		break;
	case EJob::Archer:
		std::cout << "Archer" << std::endl;
		break;
	case EJob::Mage:
		std::cout << "Mage" << std::endl;
		break;
	}
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}
