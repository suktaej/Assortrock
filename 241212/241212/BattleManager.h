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
	//friend : ������ Ŭ�������� �� Ŭ������ private�� �����㰡
	//���������� ���� ��� ����
private:
	CBattleManager();
	~CBattleManager();
private:
	EBattleMenu Menu();

public:
	bool Init();
	void Run();
};

