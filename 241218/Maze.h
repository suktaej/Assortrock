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
	//==������ ������Ʈ�� ��ġ�� �����ϴ� �迭
	int mObjectCount = 0;
	int mObjectCapacity = 4;

	int mScore = 0;
	__int64 mTime = 0;
<<<<<<< HEAD:241218/Maze.h
	
	COORD* mItemBackup = nullptr;
	int mItemCount = 0;

=======
>>>>>>> 3b54cb982d9f6ac9aad46879d29b5974319ce203:241218/241218/Maze.h
public:
	bool Init(const char* FileName);
	void Output();
	void Run();

	void ResetItems();
	ETileType GetTile(int x, int y) const;
	const char* GetName() const { return mName; }
	__int64 GetTime() const { return mTime; }
	int GetScore() const { return mScore; }

	void SetFunc(FILE* InputFile);
	void SetFunc();
	void ArrayRedef();
};
