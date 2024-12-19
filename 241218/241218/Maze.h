#pragma once

#include "Gameinfo.h"

class CMaze
{
private:
	ETileType** mMazeArray = nullptr;
	COORD mStartPos;
	//���������� Ȯ�� ������ �迭 ����
	char* mOutputBuffer = nullptr;
	//��¿� �̷� ����
	//ũ�⸦ �� �� ���� �̷ε��� �ҷ����Ƿ� �����迭�� �Ҵ��ؾ� ��
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

