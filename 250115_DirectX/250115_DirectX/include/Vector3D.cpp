
#include "Vector3D.h"
#include "Matrix.h"

#pragma region Construction

FVector3D::FVector3D()
{
}

FVector3D::FVector3D(float _x, float _y, float _z) :
	x(_x),
	y(_y),
	z(_z)
{
}

FVector3D::FVector3D(const FVector3D& v) :
	x(v.x),
	y(v.y),
	z(v.z)
{
}

FVector3D::FVector3D(FVector3D&& v) :
	x(v.x),
	y(v.y),
	z(v.z)
{
}

FVector3D::FVector3D(const DirectX::XMVECTOR& v)
{
	// XMVECTOR�� XMFLOAT3�� ������ش�.
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);
}

#pragma endregion Construction

#pragma region Equal

const FVector3D& FVector3D::operator = (const FVector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

const FVector3D& FVector3D::operator = (const DirectX::XMVECTOR& v)
{
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);
	return *this;
}

const FVector3D& FVector3D::operator = (float Value)
{
	x = Value;
	y = Value;
	z = Value;
	return *this;
}

const FVector3D& FVector3D::operator = (double Value)
{
	x = (float)Value;
	y = (float)Value;
	z = (float)Value;
	return *this;
}

const FVector3D& FVector3D::operator = (int Value)
{
	x = (float)Value;
	y = (float)Value;
	z = (float)Value;
	return *this;
}

#pragma endregion Equal

#pragma region Plus
// +
FVector3D FVector3D::operator + (const FVector3D& v)	const
{
	FVector3D	result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

FVector3D FVector3D::operator + (float Value)	const
{
	FVector3D	result;
	result.x = x + Value;
	result.y = y + Value;
	result.z = z + Value;
	return result;
}

FVector3D FVector3D::operator + (double Value)	const
{
	FVector3D	result;
	result.x = x + (float)Value;
	result.y = y + (float)Value;
	result.z = z + (float)Value;
	return result;
}

FVector3D FVector3D::operator + (int Value)	const
{
	FVector3D	result;
	result.x = x + (float)Value;
	result.y = y + (float)Value;
	result.z = z + (float)Value;
	return result;
}

// +=
const FVector3D& FVector3D::operator += (const FVector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

const FVector3D& FVector3D::operator += (float Value)
{
	x += Value;
	y += Value;
	z += Value;
	return *this;
}

const FVector3D& FVector3D::operator += (double Value)
{
	x += (float)Value;
	y += (float)Value;
	z += (float)Value;
	return *this;
}

const FVector3D& FVector3D::operator += (int Value)
{
	x += (float)Value;
	y += (float)Value;
	z += (float)Value;
	return *this;
}

// ++
const FVector3D& FVector3D::operator ++ ()
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	return *this;
}

const FVector3D& FVector3D::operator ++ (int)
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	return *this;
}

#pragma endregion Plus

#pragma region Minus
// -
FVector3D FVector3D::operator - (const FVector3D& v)	const
{
	FVector3D	result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

FVector3D FVector3D::operator - (float Value)	const
{
	FVector3D	result;
	result.x = x - Value;
	result.y = y - Value;
	result.z = z - Value;
	return result;
}

FVector3D FVector3D::operator - (double Value)	const
{
	FVector3D	result;
	result.x = x - (float)Value;
	result.y = y - (float)Value;
	result.z = z - (float)Value;
	return result;
}

FVector3D FVector3D::operator - (int Value)	const
{
	FVector3D	result;
	result.x = x - (float)Value;
	result.y = y - (float)Value;
	result.z = z - (float)Value;
	return result;
}

// -=
const FVector3D& FVector3D::operator -= (const FVector3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

const FVector3D& FVector3D::operator -= (float Value)
{
	x -= Value;
	y -= Value;
	z -= Value;
	return *this;
}

const FVector3D& FVector3D::operator -= (double Value)
{
	x -= (float)Value;
	y -= (float)Value;
	z -= (float)Value;
	return *this;
}

const FVector3D& FVector3D::operator -= (int Value)
{
	x -= (float)Value;
	y -= (float)Value;
	z -= (float)Value;
	return *this;
}

// --
const FVector3D& FVector3D::operator -- ()
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	return *this;
}

const FVector3D& FVector3D::operator -- (int)
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	return *this;
}

#pragma endregion Minus

#pragma region Multiply

// *
FVector3D FVector3D::operator * (const FVector3D& v)	const
{
	FVector3D	result;
	result.x = x * v.x;
	result.y = y * v.y;
	result.z = z * v.z;
	return result;
}

FVector3D FVector3D::operator * (float Value)	const
{
	FVector3D	result;
	result.x = x * Value;
	result.y = y * Value;
	result.z = z * Value;
	return result;
}

FVector3D FVector3D::operator * (double Value)	const
{
	FVector3D	result;
	result.x = x * (float)Value;
	result.y = y * (float)Value;
	result.z = z * (float)Value;
	return result;
}

FVector3D FVector3D::operator * (int Value)	const
{
	FVector3D	result;
	result.x = x * (float)Value;
	result.y = y * (float)Value;
	result.z = z * (float)Value;
	return result;
}

// *=
const FVector3D& FVector3D::operator *= (const FVector3D& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

const FVector3D& FVector3D::operator *= (float Value)
{
	x *= Value;
	y *= Value;
	z *= Value;
	return *this;
}

const FVector3D& FVector3D::operator *= (double Value)
{
	x *= (float)Value;
	y *= (float)Value;
	z *= (float)Value;
	return *this;
}

const FVector3D& FVector3D::operator *= (int Value)
{
	x *= (float)Value;
	y *= (float)Value;
	z *= (float)Value;
	return *this;
}

#pragma endregion Multiply

#pragma region Divide

// /
FVector3D FVector3D::operator / (const FVector3D& v)	const
{
	FVector3D	result;
	result.x = x / v.x;
	result.y = y / v.y;
	result.z = z / v.z;
	return result;
}

FVector3D FVector3D::operator / (float Value)	const
{
	FVector3D	result;
	result.x = x / Value;
	result.y = y / Value;
	result.z = z / Value;
	return result;
}

FVector3D FVector3D::operator / (double Value)	const
{
	FVector3D	result;
	result.x = x / (float)Value;
	result.y = y / (float)Value;
	result.z = z / (float)Value;
	return result;
}

FVector3D FVector3D::operator / (int Value)	const
{
	FVector3D	result;
	result.x = x / (float)Value;
	result.y = y / (float)Value;
	result.z = z / (float)Value;
	return result;
}

// /=
const FVector3D& FVector3D::operator /= (const FVector3D& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

const FVector3D& FVector3D::operator /= (float Value)
{
	x /= Value;
	y /= Value;
	z /= Value;
	return *this;
}

const FVector3D& FVector3D::operator /= (double Value)
{
	x /= (float)Value;
	y /= (float)Value;
	z /= (float)Value;
	return *this;
}

const FVector3D& FVector3D::operator /= (int Value)
{
	x /= (float)Value;
	y /= (float)Value;
	z /= (float)Value;
	return *this;
}

#pragma endregion Divide

#pragma region Function

float FVector3D::Length()	const
{
	// sqrtf : ��Ʈ�� �����ִ� ���.
	return sqrtf(x * x + y * y + z * z);
}

void FVector3D::Normalize()
{
	float	Size = Length();

	if (Size == 0.f)
		return;

	x /= Size;
	y /= Size;
	z /= Size;
}

FVector3D FVector3D::Normalize(const FVector3D& v)
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

float FVector3D::Dot(const FVector3D& v)	const
{
	return x * v.x + y * v.y + z * v.z;
}

FVector3D FVector3D::Cross(const FVector3D& v)	const
{
	FVector3D	result;
	result.x = y * v.z - z * v.y;
	result.y = z * v.x - x * v.z;
	result.z = x * v.y - y * v.x;
	return result;
}

float FVector3D::Distance(const FVector3D& v)	const
{
	FVector3D v1 = *this - v;

	return v1.Length();
}

DirectX::XMVECTOR FVector3D::Convert()	const
{
	return DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this);
}

FVector3D FVector3D::TransformNormal(FMatrix& mat)	const
{
	// XMVector3TransformNormal : w�� 0���� �Ͽ� 4x4 ��İ� ���ϰ� �� �����
	// ��ȯ���ش�.
	DirectX::XMVECTOR result = DirectX::XMVector3TransformNormal(Convert(),
		mat.m);

	return result;
}

FVector3D FVector3D::TransformCoord(FMatrix& mat)	const
{
	// XMVector3TransformCoord : w�� 1�� �Ͽ� 4x4 ��İ� ���ϰ� �� �����
	// ��ȯ���ش�.
	DirectX::XMVECTOR result = DirectX::XMVector3TransformCoord(Convert(),
		mat.m);

	return result;
}

FVector3D FVector3D::GetRotation(const FVector3D& Rot)	const
{
	FMatrix	matRot;

	matRot.Rotation(Rot);

	return TransformNormal(matRot);
}

#pragma endregion Function