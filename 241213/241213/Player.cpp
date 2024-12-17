#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	std::cout << "Player init" << std::endl;
    return true;
}

void CPlayer::SetJob(EJob NewJob)
{
	mJob = NewJob;
}

void CPlayer::Output()
{
	CCharacter::Output();
	switch (mJob)
	{
	case EJob::Fighter:
		std::cout << "직업 : 전사" << std::endl;
		break;
	case EJob::Archer:
		std::cout << "직업 : 궁수" << std::endl;
		break;
	case EJob::Mage:
		std::cout << "직업 : 마법사" << std::endl;
		break;
	}
}
