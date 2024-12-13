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

void CPlayer::Output()
{
	CCharacter::Output();
}
