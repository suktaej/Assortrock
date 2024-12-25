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
	//��¿� 1���� �迭
	int mPrevPlayerIndex = 0;
	char mPrevplayerOutput;
	//��¿� �迭���� �÷��̾� ���� �������� �ε���

	class CObject** mObjectList = nullptr;
	//������ ���(������Ʈ �ּҸ� �����ϴ� ������ ���� �迭)
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

