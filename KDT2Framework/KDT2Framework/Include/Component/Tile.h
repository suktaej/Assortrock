#pragma once

#include "../GameInfo.h"

class CTile
{
	friend class CTileMapComponent;

private:
	CTile();
	~CTile();

private:
	FVector2D	mPos;
	FVector2D	mSize;
	FVector2D	mCenter;
};

