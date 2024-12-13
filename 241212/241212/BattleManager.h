#pragma once

#include "GameInfo.h"

enum class EBattleMenu
{
	None,
	Easy,
	Normal,
	Hard,
	Back
};

class CBattleManager
{
	friend class CGameManager;
	//friend : 지정한 클래스에서 이 클래스의 private에 접근허가
	//제한적으로 사용될 경우 유용
private:
	CBattleManager();
	~CBattleManager();
private:
	EBattleMenu Menu();

public:
	bool Init();
	void Run();
};

