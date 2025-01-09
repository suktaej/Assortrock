#pragma once
#include "Object.h"
class FPlayer :
    public FObject
{
public:
    FPlayer();
    ~FPlayer() override;

private:
    class FMaze* m_Maze = nullptr;
    int m_HP = 5;
public:
	void SetMaze(FMaze* Maze) { m_Maze = Maze; }
	int GetHP()	const { return m_HP; }
	bool AddHP(int Damage)
	{
		m_HP += Damage;

		if (m_HP > 5)
			m_HP = 5;

		return m_HP <= 0;
	}
public:
	bool Init() override;
	void Update() override;
	void Output(char* Buffer, int CountX) override;
};

