#pragma once

#include <math.h>
#include "EngineMath.h"

struct FVector3D
{
	float	x = 0.f;
	float	y = 0.f;
	float	z = 0.f;

#pragma region Construction

	FVector3D();

	FVector3D(float _x, float _y, float _z);

	FVector3D(const FVector3D& v);

	FVector3D(FVector3D&& v);

	FVector3D(const DirectX::XMVECTOR& v);

#pragma endregion Construction

#pragma region Equal

	const FVector3D& operator = (const FVector3D& v);

	const FVector3D& operator = (const DirectX::XMVECTOR& v);

	const FVector3D& operator = (float Value);

	const FVector3D& operator = (double Value);

	const FVector3D& operator = (int Value);

#pragma endregion Equal

#pragma region Plus
	// +
	FVector3D operator + (const FVector3D& v)	const;

	FVector3D operator + (float Value)	const;

	FVector3D operator + (double Value)	const;

	FVector3D operator + (int Value)	const;

	// +=
	const FVector3D& operator += (const FVector3D& v);

	const FVector3D& operator += (float Value);

	const FVector3D& operator += (double Value);

	const FVector3D& operator += (int Value);

	// ++
	const FVector3D& operator ++ ();

	const FVector3D& operator ++ (int);

#pragma endregion Plus

#pragma region Minus
	// -
	FVector3D operator - (const FVector3D& v)	const;

	FVector3D operator - (float Value)	const;

	FVector3D operator - (double Value)	const;

	FVector3D operator - (int Value)	const;

	// -=
	const FVector3D& operator -= (const FVector3D& v);

	const FVector3D& operator -= (float Value);

	const FVector3D& operator -= (double Value);

	const FVector3D& operator -= (int Value);

	// --
	const FVector3D& operator -- ();

	const FVector3D& operator -- (int);

#pragma endregion Minus

#pragma region Multiply

	// *
	FVector3D operator * (const FVector3D& v)	const;

	FVector3D operator * (float Value)	const;

	FVector3D operator * (double Value)	const;

	FVector3D operator * (int Value)	const;

	// *=
	const FVector3D& operator *= (const FVector3D& v);

	const FVector3D& operator *= (float Value);

	const FVector3D& operator *= (double Value);

	const FVector3D& operator *= (int Value);

#pragma endregion Multiply

#pragma region Divide

	// /
	FVector3D operator / (const FVector3D& v)	const;

	FVector3D operator / (float Value)	const;

	FVector3D operator / (double Value)	const;

	FVector3D operator / (int Value)	const;

	// /=
	const FVector3D& operator /= (const FVector3D& v);

	const FVector3D& operator /= (float Value);

	const FVector3D& operator /= (double Value);

	const FVector3D& operator /= (int Value);

#pragma endregion Divide

#pragma region Function

	float Length()	const;

	void Normalize();


	static FVector3D Normalize(const FVector3D& v);

	float Dot(const FVector3D& v)	const;

	FVector3D Cross(const FVector3D& v)	const;

	float Distance(const FVector3D& v)	const;

	DirectX::XMVECTOR Convert()	const;

	FVector3D TransformNormal(union FMatrix& mat)	const;

	FVector3D TransformCoord(union FMatrix& mat)	const;

	FVector3D GetRotation(const FVector3D& Rot)	const;

#pragma endregion Function
};
