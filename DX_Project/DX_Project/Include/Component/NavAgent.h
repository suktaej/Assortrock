#pragma once

#include "../GameInfo.h"

class CNavAgent
{
protected:
	CNavAgent();
	CNavAgent(const CNavAgent& Com);
	CNavAgent(CNavAgent&& Com);
	~CNavAgent();

public:
	std::list<FVector2D>	mPathList;

public:
	bool FindPath(const FVector2D& Start,
		const FVector2D& End);
	bool FindPath(const FVector3D& Start,
		const FVector2D& End);
	bool FindPath(const FVector3D& Start,
		const FVector3D& End);
};

