#pragma once
#include "GameInfo.h"

enum class EBattleType
{
	None,
	Easy,
	Normal,
	Hard,
	Back
};

class CBattleManager
{
private:
	CBattleManager();
	~CBattleManager();
private:
	EBattleType Menu();
public:
	bool Init();
	void Run();

};

