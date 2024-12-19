#pragma once

#include "Gameinfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();
private:
	ETileType** mMazeArray = nullptr;
	//������ �迭 ����
	COORD mStartPos;
	COORD mGoalPos;
	char* mOutputBuffer = nullptr;
	//��¿� �̷� ����
	//ũ�⸦ �� �� ���� �̷ε��� �ҷ����Ƿ� �����迭�� �Ҵ��ؾ� ��
	char mPrevPlayerOutput;
	int mPrevPlayerIndex = 0;
	//�÷��̾��� ���� ������ �ε����� ����
	int mCountX;
	int mCountY;
	char mName[32] = {};

	class CObject** mObjectList = nullptr;
	//������Ʈ �ּҸ� �����ϴ� ������ ���� �迭
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

