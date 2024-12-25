#pragma once
#include "Object.h"

class CPlayer:public CObject
{
public:
	CPlayer();
	~CPlayer() override;
private:
	class CMaze* mMaze = nullptr;
public:
	bool Init() override;
	void Update() override;
	void Output() override;
	void Output(char* OutBuffer,int CountX) override;
	void SetMaze(CMaze* Maze) { mMaze = Maze; }
};
