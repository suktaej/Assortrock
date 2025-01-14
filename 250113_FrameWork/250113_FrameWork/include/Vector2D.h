#pragma once
#include <cmath>

struct FVector2D
{
	float x = 0.f;
	float y = 0.f;

	FVector2D() {}
	FVector2D(float _x, float _y) :x(_x), y(_y) {}
	FVector2D(const FVector2D& v) :x(v.x), y(v.y) {}
	FVector2D(FVector2D&& v) :x(v.x), y(v.y) {}

	const FVector2D& operator=(const FVector2D& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	const FVector2D& operator = (float Value)
	{
		x = Value;
		y = Value;
		return *this;
	}
	const FVector2D& operator = (int Value)
	{
		x = (float)Value;
		y = (float)Value;
		return *this;
	}
	const FVector2D& operator = (double Value)
	{
		x = (float)Value;
		y = (float)Value;
		return *this;
	}
#pragma region Plus
	FVector2D operator + (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x + v.x;
		result.y = y + v.y;
		return result;
	}
	FVector2D operator + (float Value ) const
	{
		FVector2D result;
		result.x = x + Value;
		result.y = y + Value;
		return result;
	}

	FVector2D operator + (int Value ) const
	{
		FVector2D result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		return result;
	}
	FVector2D operator + (double Value ) const
	{
		FVector2D result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		return result;
	}
	const FVector2D& operator += (float Value)
	{
		x += Value;
		y += Value;
		return *this;
	}
	const FVector2D& operator += (int Value)
	{
		x += (float)Value;
		y += (float)Value;
		return *this;
	}
	const FVector2D& operator += (double Value)
	{
		x += (float)Value;
		y += (float)Value;
		return *this;
	}

	const FVector2D& operator++()
	{
		x += 1.f;
		y += 1.f;
		return *this;
	}
	const FVector2D& operator++(int)
	{
		x += 1.f;
		y += 1.f;
		return *this;
	}
#pragma endregion Plus

#pragma region Minus
	FVector2D operator - (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x - v.x;
		result.y = y - v.y;
		return result;
	}
	FVector2D operator - (float Value ) const
	{
		FVector2D result;
		result.x = x - Value;
		result.y = y - Value;
		return result;
	}

	FVector2D operator - (int Value ) const
	{
		FVector2D result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		return result;
	}
	FVector2D operator - (double Value ) const
	{
		FVector2D result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		return result;
	}
	const FVector2D& operator -= (float Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		return *this;
	}
	const FVector2D& operator -= (int Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		return *this;
	}
	const FVector2D& operator -= (double Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		return *this;
	}

	const FVector2D& operator--()
	{
		x -= 1.f;
		y -= 1.f;
		return *this;
	}
	const FVector2D& operator--(int)
	{
		x -= 1.f;
		y -= 1.f;
		return *this;
	}
#pragma endregion Minus

#pragma region Multiply
	FVector2D operator * (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x * v.x;
		result.y = y * v.y;
		return result;
	}
	FVector2D operator * (float Value ) const
	{
		FVector2D result;
		result.x = x * Value;
		result.y = y * Value;
		return result;
	}

	FVector2D operator * (int Value ) const
	{
		FVector2D result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		return result;
	}
	FVector2D operator * (double Value ) const
	{
		FVector2D result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		return result;
	}
	const FVector2D& operator *= (float Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		return *this;
	}
	const FVector2D& operator *= (int Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		return *this;
	}
	const FVector2D& operator *= (double Value)
	{
		x *= (float)Value;
		y += (float)Value;
		return *this;
	}

#pragma endregion Multiply

#pragma region Divide
	FVector2D operator / (const FVector2D& v) const
	{
		FVector2D result;
		result.x = x / v.x;
		result.y = y / v.y;
		return result;
	}
	FVector2D operator / (float Value ) const
	{
		FVector2D result;
		result.x = x / Value;
		result.y = y / Value;
		return result;
	}

	FVector2D operator / (int Value ) const
	{
		FVector2D result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		return result;
	}
	FVector2D operator / (double Value ) const
	{
		FVector2D result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		return result;
	}
	const FVector2D& operator /= (float Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		return *this;
	}
	const FVector2D& operator /= (int Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		return *this;
	}
	const FVector2D& operator /= (double Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		return *this;
	}

#pragma endregion Divide

	float Length() const { return sqrtf(x*x+y*y); }
	float Dot(const FVector2D& v) const { return x * v.x + y*v.y; }
	FVector2D Cross(const FVector2D& v) const { }
	
	void Normalize()
	{
		float Size = Length();
		x /= Size;
		y /= Size;
	}

	static FVector2D Normalize(const FVector2D& v)
	{
		FVector2D result;
		float Size = v.Length();
		result.x = v.x / Size;
		result.y = v.y / Size;

		return result;
	}

	float Distance(const FVector2D& v) const
	{
		FVector2D v1 = *this - v;
		return v1.Length();
	}



	
};
