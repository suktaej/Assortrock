#pragma once
#include "GameInfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();
private:
	ETileType** mMazeArray = nullptr;
	int mXsize = 0;
	int mYsize = 0;

	char mName[32] = {};
	COORD mStartPos;
	COORD mGoalPos;

	char* mOutputBuffer;
	//출력용 1차원 배열
	int mPrevPlayerIndex = 0;
	char mPrevplayerOutput;
	//출력용 배열에서 플레이어 이전 프레임의 인덱스

	class CObject** mObjectList = nullptr;
	//아이템 출력(오브젝트 주소를 저장하는 포인터 가변 배열)
	int mObjectCount = 0;
	int mObjectCapacity = DEFAULT_CAPACITY;

public:
	bool Init();
	bool Init(const char* FileName);
	void Run();
	void Output();
	void HideCursor();
	const char* GetName() const { return mName; }
	ETileType GetTile(int x, int y) const; 
};

