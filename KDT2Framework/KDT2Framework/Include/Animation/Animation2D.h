#pragma once

#include "../GameInfo.h"

class CAnimation2D
{
	friend class CSpriteComponent;

private:
	CAnimation2D();
	CAnimation2D(const CAnimation2D& Anim);
	~CAnimation2D();

private:
	class CScene* mScene = nullptr;
	class CSpriteComponent* mOwner = nullptr;
	std::unordered_map<std::string, class CAnimation2DSequence*>	mSequenceMap;
	class CAnimation2DSequence* mCurrentSequence = nullptr;

public:
	bool Init();
	void Update(float DeltaTime);
	bool AddSequence(const std::string& Name,
		float PlayTime = 1.f, float PlayRate = 1.f,
		bool Loop = false, bool Reverse = false);
	bool AddSequence(class CAnimation2DData* Asset,
		float PlayTime = 1.f, float PlayRate = 1.f,
		bool Loop = false, bool Reverse = false);
	void SetPlayTime(const std::string& Name,
		float PlayTime);
	void SetPlayRate(const std::string& Name,
		float PlayRate);
	void SetLoop(const std::string& Name,
		bool Loop);
	void SetReverse(const std::string& Name,
		bool Reverse);
	void ChangeAnimation(const std::string& Name);
	CAnimation2D* Clone();
	void SetShader();
	
private:
	class CAnimation2DSequence* FindSequence(
		const std::string& Name);
};

