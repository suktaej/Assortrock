#pragma once

#include "Gameinfo.h"

class CMaze
{
private:
	ETileType** mMazeArray = nullptr;
	COORD mStartPos;
	//이중포인터 확인 이차원 배열 형식
	char* mOutputBuffer = nullptr;
	//출력용 미로 버퍼
	//크기를 알 수 없는 미로들을 불러오므로 동적배열로 할당해야 함
	int mCountX;
	int mCountY;
	char mName[32] = {};
public:
	CMaze();
	~CMaze();
public:
	const char* GetName() const { return mName; }
	bool Init(const char* FileName);
	void Output();
	void Run();
};

