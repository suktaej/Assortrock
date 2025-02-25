#pragma once

#include "../GameInfo.h"

class CTile
{
	friend class CTileMapComponent;

private:
	CTile();
	~CTile();

private:
	ETileType	mType = ETileType::None;
	FVector2D	mPos;
	FVector2D	mSize;
	FVector2D	mCenter;

public:
	ETileType GetType()	const
	{
		return mType;
	}

public:
	void SetTileType(ETileType Type)
	{
		mType = Type;
	}
};

