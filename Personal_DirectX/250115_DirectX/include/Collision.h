#pragma once

#include "GameInfo.h"

class CCollision
{
public:
	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderAABB2D* Dest);
	static bool CollisionSphere2DToSphere2D(FVector3D& HitPoint,
		class CColliderSphere2D* Src,
		class CColliderSphere2D* Dest);
	static bool CollisionAABB2DToSphere2D(FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderSphere2D* Dest);
	static bool CollisionOBB2DToOBB2D(FVector3D& HitPoint,
		class CColliderOBB2D* Src,
		class CColliderOBB2D* Dest);
	static bool CollisionAABB2DToOBB2D(FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderOBB2D* Dest);
	static bool CollisionSphere2DToOBB2D(FVector3D& HitPoint,
		class CColliderSphere2D* Src,
		class CColliderOBB2D* Dest);

	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint,
		const FAABB2D& Src,	const FAABB2D& Dest);
	static bool CollisionSphere2DToSphere2D(FVector3D& HitPoint,
		const FVector3D& SrcCenter, float SrcRadius,
		const FVector3D& DestCenter, float DestRadius);
	static bool CollisionAABB2DToSphere2D(FVector3D& HitPoint,
		const FAABB2D& Src,
		const FVector3D& DestCenter, float DestRadius);
	static bool CollisionOBB2DToOBB2D(FVector3D& HitPoint,
		const FOBB2D& Src, const FOBB2D& Dest);
	static bool CollisionAABB2DToOBB2D(FVector3D& HitPoint,
		const FAABB2D& Src, const FOBB2D& Dest);
	static bool CollisionSphere2DToOBB2D(FVector3D& HitPoint,
		const FVector3D& SrcCenter, float SrcRadius,
		const FOBB2D& Dest);

private:
	static bool ComputeAxisProjection(const FVector2D& CenterLine,
		const FVector2D& SeparationAxis,
		float AxisHalfSize, const FVector2D* DestAxis,
		const FVector2D& DestHalfSize);

	static FAABB2D CreateAABB2D(const FOBB2D& Info);
	static FAABB2D CreateAABB2D(const FVector2D& Center,
		float Radius);
	static FOBB2D CreateOBB2D(const FAABB2D& Info);
};

