#pragma once
#include "GameInfo.h"

class FStage
{
public:
	FStage();
	~FStage();
private:
	char* m_OutputBuffer;
	const int k_Xsize = 12;
	//º®¸é:2 ¸Ê:10
	const int k_Ysize = 10;
	//º®¸é:2 ¸Ê:20 »ó´Ü °ø°£:4 

	LARGE_INTEGER m_Time;
	LARGE_INTEGER m_Second;
	float m_DeltaTime = 0.f;
	float m_StageTime = 0.f;

	class FObject* m_CurrentBlock;
	std::list<FObject*> m_StackedBlock;
	bool m_BlockActive = true;

public:
	bool Init();
	void Run();
	void CreateBlock();
	void CreateMap();
	void Output();

	int GetXsize() { return k_Xsize; }
	int GetYsize() { return k_Ysize; }
	void SetActive() { m_BlockActive = true; }
};
