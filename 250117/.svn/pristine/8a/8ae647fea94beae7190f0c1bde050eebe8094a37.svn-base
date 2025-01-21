#pragma once

#include <math.h>
#include "EngineMath.h"

struct FVector3D
{
	float	x = 0.f;
	float	y = 0.f;
	float	z = 0.f;

#pragma region Construction

	FVector3D()
	{
	}

	FVector3D(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{
	}

	FVector3D(const FVector3D& v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{
	}

	FVector3D(FVector3D&& v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{
	}

#pragma endregion Construction

#pragma region Equal

	const FVector3D& operator = (const FVector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	const FVector3D& operator = (float Value)
	{
		x = Value;
		y = Value;
		z = Value;
		return *this;
	}

	const FVector3D& operator = (double Value)
	{
		x = (float)Value;
		y = (float)Value;
		z = (float)Value;
		return *this;
	}

	const FVector3D& operator = (int Value)
	{
		x = (float)Value;
		y = (float)Value;
		z = (float)Value;
		return *this;
	}

#pragma endregion Equal

#pragma region Plus
	// +
	FVector3D operator + (const FVector3D& v)	const
	{
		FVector3D	result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;
		return result;
	}

	FVector3D operator + (float Value)	const
	{
		FVector3D	result;
		result.x = x + Value;
		result.y = y + Value;
		result.z = z + Value;
		return result;
	}

	FVector3D operator + (double Value)	const
	{
		FVector3D	result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		result.z = z + (float)Value;
		return result;
	}

	FVector3D operator + (int Value)	const
	{
		FVector3D	result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		result.z = z + (float)Value;
		return result;
	}

	// +=
	const FVector3D& operator += (const FVector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	const FVector3D& operator += (float Value)
	{
		x += Value;
		y += Value;
		z += Value;
		return *this;
	}

	const FVector3D& operator += (double Value)
	{
		x += (float)Value;
		y += (float)Value;
		z += (float)Value;
		return *this;
	}

	const FVector3D& operator += (int Value)
	{
		x += (float)Value;
		y += (float)Value;
		z += (float)Value;
		return *this;
	}

	// ++
	const FVector3D& operator ++ ()
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;
		return *this;
	}

	const FVector3D& operator ++ (int)
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;
		return *this;
	}

#pragma endregion Plus

#pragma region Minus
	// -
	FVector3D operator - (const FVector3D& v)	const
	{
		FVector3D	result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;
		return result;
	}

	FVector3D operator - (float Value)	const
	{
		FVector3D	result;
		result.x = x - Value;
		result.y = y - Value;
		result.z = z - Value;
		return result;
	}

	FVector3D operator - (double Value)	const
	{
		FVector3D	result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		result.z = z - (float)Value;
		return result;
	}

	FVector3D operator - (int Value)	const
	{
		FVector3D	result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		result.z = z - (float)Value;
		return result;
	}

	// -=
	const FVector3D& operator -= (const FVector3D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	const FVector3D& operator -= (float Value)
	{
		x -= Value;
		y -= Value;
		z -= Value;
		return *this;
	}

	const FVector3D& operator -= (double Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		z -= (float)Value;
		return *this;
	}

	const FVector3D& operator -= (int Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		z -= (float)Value;
		return *this;
	}

	// --
	const FVector3D& operator -- ()
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		return *this;
	}

	const FVector3D& operator -- (int)
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		return *this;
	}

#pragma endregion Minus

#pragma region Multiply

	// *
	FVector3D operator * (const FVector3D& v)	const
	{
		FVector3D	result;
		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;
		return result;
	}

	FVector3D operator * (float Value)	const
	{
		FVector3D	result;
		result.x = x * Value;
		result.y = y * Value;
		result.z = z * Value;
		return result;
	}

	FVector3D operator * (double Value)	const
	{
		FVector3D	result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		result.z = z * (float)Value;
		return result;
	}

	FVector3D operator * (int Value)	const
	{
		FVector3D	result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		result.z = z * (float)Value;
		return result;
	}

	// *=
	const FVector3D& operator *= (const FVector3D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	const FVector3D& operator *= (float Value)
	{
		x *= Value;
		y *= Value;
		z *= Value;
		return *this;
	}

	const FVector3D& operator *= (double Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		z *= (float)Value;
		return *this;
	}

	const FVector3D& operator *= (int Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		z *= (float)Value;
		return *this;
	}

#pragma endregion Multiply

#pragma region Divide

	// /
	FVector3D operator / (const FVector3D& v)	const
	{
		FVector3D	result;
		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;
		return result;
	}

	FVector3D operator / (float Value)	const
	{
		FVector3D	result;
		result.x = x / Value;
		result.y = y / Value;
		result.z = z / Value;
		return result;
	}

	FVector3D operator / (double Value)	const
	{
		FVector3D	result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		result.z = z / (float)Value;
		return result;
	}

	FVector3D operator / (int Value)	const
	{
		FVector3D	result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		result.z = z / (float)Value;
		return result;
	}

	// /=
	const FVector3D& operator /= (const FVector3D& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	const FVector3D& operator /= (float Value)
	{
		x /= Value;
		y /= Value;
		z /= Value;
		return *this;
	}

	const FVector3D& operator /= (double Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		z /= (float)Value;
		return *this;
	}

	const FVector3D& operator /= (int Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		z /= (float)Value;
		return *this;
	}

#pragma endregion Divide

#pragma region Function

	float Length()	const
	{
		// sqrtf : 루트값 구해주는 기능.
		return sqrtf(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float	Size = Length();

		if (Size == 0.f)
			return;

		x /= Size;
		y /= Size;
		z /= Size;
	}


	static FVector3D Normalize(const FVector3D& v)
	{
		FVector3D	result;
		float	Size = v.Length();

		if (Size == 0.f)
			return result;

		result.x = v.x / Size;
		result.y = v.y / Size;
		result.z = v.z / Size;
		return result;
	}

	float Dot(const FVector3D& v)	const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	FVector3D Cross(const FVector3D& v)	const
	{
		FVector3D	result;
		result.x = y * v.z - z * v.y;
		result.y = z * v.x - x * v.z;
		result.z = x * v.y - y * v.x;
		return result;
	}

	float Distance(const FVector3D& v)	const
	{
		FVector3D v1 = *this - v;

		return v1.Length();
	}

#pragma endregion Function
};
