#pragma once

#include "../GameInfo.h"

class CTile
{
	friend class CTileMapComponent;

private:
	CTile();
	~CTile();

private:
	ETileType	mType = ETileType::Normal;
	FVector2D	mPos;
	FVector2D	mSize;
	FVector2D	mCenter;

public:
	ETileType GetType()	const
	{
		return mType;
	}

	const FVector2D& GetPos()	const
	{
		return mPos;
	}

	const FVector2D& GetCenter()	const
	{
		return mCenter;
	}

	const FVector2D& GetSize()	const
	{
		return mSize;
	}

public:
	void SetTileType(ETileType Type)
	{
		mType = Type;
	}
};

