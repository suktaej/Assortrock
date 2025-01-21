#pragma once

#include "Vector4D.h"

//하나의 메모리를 공통으로 사용
//directX에서 대부분 16byte를 사용
__declspec(align(16)) union FMatrix
{
	//__declspec : 메모리 정렬을 16byte로 만들어준다
	//SIMD 연산을 지원하는 타입으로 변환
	//XMMATRIX를 사용해 랩핑
	//XMMATRIX는 4x4 행렬이므로 64byte

	//64byte
	//union 내에서 최대 메모리크기 확보
	DirectX::XMMATRIX m;

	//구조체명이 없을 경우 
	//내부의 변수들을 합해서 하나의 메모리로 처리
	struct
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};
	
	//float 2차원 배열
	float Value[4][4];
	
	//4D 구조체
	FVector4D v[4];

	FMatrix() 
	{
		//항등행렬 생성함수
		m = DirectX::XMMatrixIdentity();
	}
	FMatrix(const FMatrix& _m) { m = _m.m; }
	FMatrix(FMatrix&& _m) { m = _m.m; }
	FMatrix(const DirectX::XMMATRIX& _m) { m = _m; }
	FMatrix(const FVector4D _v[4]) { memcpy(v, _v, sizeof(FVector4D) * 4); }

	FVector4D& operator [] (int Index) 
	{
		assert(0 <= Index && Index <= 3);
		return v[Index];
	}
	const FMatrix& operator = (const FMatrix& _m)
	{
		m = _m.m;
		return *this;
	}
	const FMatrix& operator = (const DirectX::XMMATRIX& _m)
	{
		m = _m;
		return *this;
		
	}
	const FMatrix& operator = (const FVector4D _v[4])
	{
		memcpy(v, _v, sizeof(FVector4D) * 4);
		return *this;
	}

	FMatrix operator*(const FMatrix& _m) const { return FMatrix(m * _m.m); }
	FMatrix operator*(const DirectX::XMMATRIX& _m) const { return FMatrix(m * _m); }

	void Idnetify() { m = DirectX::XMMatrixIdentity(); }	//항등행렬 생성
	void Transpose() { m = DirectX::XMMatrixTranspose(m); } //전치행렬 생성
	void Inverse() 											//역행렬 생성
	{
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m);
		//첫번째 인자 : 해당 행렬의 역행렬을 구하기 위한 식
		//XMVECTOR 타입
		//두번째 인자 : 변경하려는 행렬
		m = DirectX::XMMatrixInverse(&det,m); 

		//월드행렬의 구성요소
		//자전, 공전
	}

	void Scaling(const FVector3D& _v) { m = DirectX::XMMatrixScaling(_v.x, _v.y, _v.z); }	//스케일링
	void Scaling(float x, float y, float z) { m = DirectX::XMMatrixScaling(x, y, z); }	
	void Scaling(const FVector2D& _v) { m = DirectX::XMMatrixScaling(_v.x, _v.y, 1.f); }
	
	void Rotation(const FVector3D& _v)					//로테이션 
	{
		//DirectX::XMConvertToDegrees();
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);
		
		//x,y,z 회전값을 이용하여 사원수 도출
		//Roll : x축 회전
		//Pitch : y축 회전
		//Yaw : z축 회전
		DirectX::XMVECTOR Quat =
			DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		//사원수를 통해 회전행렬 생성
		m = DirectX::XMMatrixRotationQuaternion(Quat);

		//각각의 행렬을 회전시킨 후 회전행렬을 통해 도출하는 방식도 가능
		//DirectX::XMMatrixRotationX
		//DirectX::XMMatrixRotationY
		//DirectX::XMMatrixRotationZ
	}
	void Rotation(float _x, float _y, float _z)					//로테이션 
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);
		
		DirectX::XMVECTOR Quat =
			DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		m = DirectX::XMMatrixRotationQuaternion(Quat);

		//각각의 행렬을 회전시킨 후 회전행렬을 통해 도출하는 방식도 가능
		//DirectX::XMMatrixRotationX
		//DirectX::XMMatrixRotationY
		//DirectX::XMMatrixRotationZ
	}
	void RotationX(float _x)
	{
		float x = DirectX::XMConvertToRadians(_x);
		m = DirectX::XMMatrixRotationX(x);
	}
	void RotationY(float _y)
	{
		float y = DirectX::XMConvertToRadians(_y);
		m = DirectX::XMMatrixRotationY(y);
	}
	void RotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);
		m = DirectX::XMMatrixRotationZ(z);
	}

	void RotationAxis(const FVector3D& Axis, float _Angle)
	{
		float Angle = DirectX::XMConvertToRadians(_Angle);

		DirectX::XMVECTOR _Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);
		m = DirectX::XMMatrixRotationAxis(_Axis, Angle);
	}

	void Translation(const FVector3D& _v) { m = DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z); }	//이동
	void Translation(float x, float y, float z) { m = DirectX::XMMatrixTranslation(x, y, z); }
	void Translation(float x, float y) { m = DirectX::XMMatrixTranslation(x, y, 0.f); }

	//static 함수화
	static FMatrix StaticIdentity() { return DirectX::XMMatrixIdentity(); }
	static FMatrix StaticTranspose(const FMatrix& _m) { return DirectX::XMMatrixTranspose(_m.m); }
	static FMatrix StaticInverse(const FMatrix& _m)
	{
		DirectX::XMVECTOR	det = DirectX::XMMatrixDeterminant(_m.m);
		return DirectX::XMMatrixInverse(&det, _m.m);
	}

	static FMatrix StaticScaling(const FVector3D& _v) { return DirectX::XMMatrixScaling(_v.x, _v.y, _v.z); }
	static FMatrix StaticScaling(float x, float y, float z) { return DirectX::XMMatrixScaling(x, y, z); }
	static FMatrix StaticScaling(const FVector2D& _v) { return DirectX::XMMatrixScaling(_v.x, _v.y, 1.f); }
	static FMatrix StaticScaling(float x, float y) { return DirectX::XMMatrixScaling(x, y, 1.f); }

	static FMatrix StaticRotation(const FVector3D& _v)
	{
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		DirectX::XMVECTOR Quat =
			DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);
		return DirectX::XMMatrixRotationQuaternion(Quat);
	}

	static FMatrix StaticRotation(float _x, float _y, float _z)
	{
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		DirectX::XMVECTOR Quat =
			DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		return DirectX::XMMatrixRotationQuaternion(Quat);
	}

	static FMatrix StaticRotationX(float _x)
	{
		float x = DirectX::XMConvertToRadians(_x);
		return DirectX::XMMatrixRotationX(x);
	}

	static FMatrix StaticRotationY(float _y)
	{
		float y = DirectX::XMConvertToRadians(_y);
		return DirectX::XMMatrixRotationY(y);
	}

	static FMatrix StaticRotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);
		return DirectX::XMMatrixRotationZ(z);
	}

	static FMatrix StaticRotationAxis(const FVector3D& Axis, float _Angle)
	{
		float Angle = DirectX::XMConvertToRadians(_Angle);

		DirectX::XMVECTOR	_Axis =
			DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

		return DirectX::XMMatrixRotationAxis(_Axis, Angle);
	}

	static FMatrix StaticTranslation(const FVector3D& _v) { return DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z); }
	static FMatrix StaticTranslation(float x, float y, float z) { return DirectX::XMMatrixTranslation(x, y, z); }
	static FMatrix StaticTranslation(const FVector2D& _v) { return DirectX::XMMatrixTranslation(_v.x, _v.y, 0.f); }
	static FMatrix StaticTranslation(float x, float y) { return DirectX::XMMatrixTranslation(x, y, 0.f); }
};
