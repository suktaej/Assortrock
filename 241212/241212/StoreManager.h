#pragma once
#include "GameInfo.h"

enum class EStoreMenu
{
	None,
	Weapon,
	Armor,
	Sell,
	Back
};

//enum class EStoreMenu
//{
//	None,
//	Weapon,
//	Armor,
//	Back
//};
class CStoreManager
{
	friend class CGameManager;
private:
	CStoreManager();
	~CStoreManager();
private:
	EStoreMenu Menu();
	class CStore* mStore[static_cast<int>(EStoreType::End)] = {};
public:
	bool Init();
	void Run();
};

