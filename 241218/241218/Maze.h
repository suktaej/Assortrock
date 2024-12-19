#pragma once

#include "Gameinfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();
private:
	ETileType** mMazeArray = nullptr;
	//이차원 배열 형식
	COORD mStartPos;
	COORD mGoalPos;
	char* mOutputBuffer = nullptr;
	//출력용 미로 버퍼
	//크기를 알 수 없는 미로들을 불러오므로 동적배열로 할당해야 함
	char mPrevPlayerOutput;
	int mPrevPlayerIndex = 0;
	//플레이어의 이전 프레임 인덱스를 저장
	int mCountX;
	int mCountY;
	char mName[32] = {};

	class CObject** mObjectList = nullptr;
	//오브젝트 주소를 저장하는 포인터 가변 배열
	int mObjectCount = 0;
	int mObjectCapacity = 4;

	int mScore = 0;
	__int64 mTime = 0;

public:
	bool Init(const char* FileName);
	void Output();
	void Run();
	
	ETileType GetTile(int x, int y) const;
	const char* GetName() const { return mName; }
	__int64 GetTime() const { return mTime; }
};

