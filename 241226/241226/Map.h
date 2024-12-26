#pragma once
#include "GameInfo.h"

class CMap
{
private:
	CMap();
	~CMap();
	static CMap* mInst;
public:
	static CMap* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CMap;
		return mInst;
	}
	static void DestroyInst()
	{
		delete mInst;
		mInst = nullptr;
	}
private:
	int mMapXSize = 15;
	int mMapYSize = 15;
	//int** mMapWall = nullptr;
	std::vector<std::vector<int>> mMapWall;
	std::vector<char> mOutputBuffer;

public:
	bool Init();
	void MakeWall();
	void Output() const;
	void Run();
	int GetTile(int x, int y) const;
};

