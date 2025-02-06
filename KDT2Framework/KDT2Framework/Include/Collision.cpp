#include "Collision.h"
#include "Component/ColliderAABB2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint,
    CColliderAABB2D* Src, CColliderAABB2D* Dest)
{
    if(CollisionAABB2DToAABB2D(HitPoint, Src->GetBox(), 
        Dest->GetBox()))
        return true;

    return false;
}

bool CCollision::CollisionSphere2DToSphere2D(
    FVector3D& HitPoint, CColliderSphere2D* Src,
    CColliderSphere2D* Dest)
{
    if (CollisionSphere2DToSphere2D(HitPoint,
        Src->GetWorldPosition(), Src->GetRadius(),
        Dest->GetWorldPosition(),
        Dest->GetRadius()))
        return true;

    return false;
}

bool CCollision::CollisionAABB2DToSphere2D(
    FVector3D& HitPoint, CColliderAABB2D* Src,
    CColliderSphere2D* Dest)
{
    if (CollisionAABB2DToSphere2D(HitPoint,
        Src->GetBox(),
        Dest->GetWorldPosition(),
        Dest->GetRadius()))
        return true;

    return false;
}

bool CCollision::CollisionOBB2DToOBB2D(
    FVector3D& HitPoint, 
    CColliderOBB2D* Src, CColliderOBB2D* Dest)
{
    if (CollisionOBB2DToOBB2D(HitPoint, Src->GetBox(),
        Dest->GetBox()))
        return true;

    return false;
}

bool CCollision::CollisionAABB2DToOBB2D(
    FVector3D& HitPoint, CColliderAABB2D* Src,
    CColliderOBB2D* Dest)
{
    if (CollisionAABB2DToOBB2D(HitPoint, Src->GetBox(),
        Dest->GetBox()))
        return true;

    return false;
}

bool CCollision::CollisionSphere2DToOBB2D(
    FVector3D& HitPoint, CColliderSphere2D* Src,
    CColliderOBB2D* Dest)
{
    if (CollisionSphere2DToOBB2D(HitPoint, 
        Src->GetWorldPosition(),
        Src->GetRadius(),
        Dest->GetBox()))
        return true;

    return false;
}

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, 
    const FAABB2D& Src, const FAABB2D& Dest)
{
    if (Src.Min.x > Dest.Max.x)
        return false;

    else if (Dest.Min.x > Src.Max.x)
        return false;

    else if (Src.Min.y > Dest.Max.y)
        return false;

    else if (Dest.Min.y > Src.Max.y)
        return false;

    FVector3D   Min, Max;
    Min.x = Src.Min.x > Dest.Min.x ? Src.Min.x : Dest.Min.x;
    Min.y = Src.Min.y > Dest.Min.y ? Src.Min.y : Dest.Min.y;

    Max.x = Src.Max.x < Dest.Max.x ? Src.Max.x : Dest.Max.x;
    Max.y = Src.Max.y < Dest.Max.y ? Src.Max.y : Dest.Max.y;

    HitPoint.x = (Min.x + Max.x) * 0.5f;
    HitPoint.y = (Min.y + Max.y) * 0.5f;

    return true;
}

bool CCollision::CollisionSphere2DToSphere2D(
    FVector3D& HitPoint, const FVector3D& SrcCenter, 
    float SrcRadius, 
    const FVector3D& DestCenter, float DestRadius)
{
    float Dist = SrcCenter.Distance(DestCenter);

    if (Dist <= SrcRadius + DestRadius)
    {
        float   Gap = SrcRadius + DestRadius - Dist;
        Gap *= 0.5f;

        FVector3D   Dir = DestCenter - SrcCenter;
        Dir.Normalize();

        HitPoint = SrcCenter + Dir * (SrcRadius - Gap);

        return true;
    }

    return false;
}

bool CCollision::CollisionAABB2DToSphere2D(
    FVector3D& HitPoint, const FAABB2D& Src,
    const FVector3D& DestCenter, float DestRadius)
{
    // 원의 중점의 x값이 원본 사각형의 좌, 우 사이에 있거나
    // 원의 중점의 y값이 원본 사각형의 위, 아래 사이에
    // 있을 경우 사각형을 원의 반지름만큼 확장하여 원의
    // 중점이 확장된 사각형 안에 있는지 판단한다.
    if ((Src.Min.x <= DestCenter.x && DestCenter.x <= Src.Max.x) ||
        (Src.Min.y <= DestCenter.y && DestCenter.y <= Src.Max.y))
    {
        // 사각형을 원의 반지름만큼 확장한다.
        FAABB2D SrcExtent;
        SrcExtent.Min = Src.Min - DestRadius;
        SrcExtent.Max = Src.Max + DestRadius;

        // 확장된 사각형 안에 원의 중점이 들어왔는지
        // 판단한다.
        if (SrcExtent.Min.x > DestCenter.x)
            return false;

        else if (SrcExtent.Max.x < DestCenter.x)
            return false;

        else if (SrcExtent.Min.y > DestCenter.y)
            return false;

        else if (SrcExtent.Max.y < DestCenter.y)
            return false;

        FAABB2D SphereAABB;

        SphereAABB.Min.x = DestCenter.x - DestRadius;
        SphereAABB.Min.y = DestCenter.y - DestRadius;
        SphereAABB.Max.x = DestCenter.x + DestRadius;
        SphereAABB.Max.y = DestCenter.y + DestRadius;

        FVector3D   Min, Max;
        Min.x = Src.Min.x > SphereAABB.Min.x ? Src.Min.x : SphereAABB.Min.x;
        Min.y = Src.Min.y > SphereAABB.Min.y ? Src.Min.y : SphereAABB.Min.y;

        Max.x = Src.Max.x < SphereAABB.Max.x ? Src.Max.x : SphereAABB.Max.x;
        Max.y = Src.Max.y < SphereAABB.Max.y ? Src.Max.y : SphereAABB.Max.y;

        HitPoint.x = (Min.x + Max.x) * 0.5f;
        HitPoint.y = (Min.y + Max.y) * 0.5f;

        return true;
    }

    // 대각 영역일 경우 해당 방향의 사각형 꼭지점을 구해준다.
    FVector3D   Vertex;

    // 왼쪽 대각선 2 영역일 경우
    if (DestCenter.x < Src.Min.x)
    {
        Vertex.x = Src.Min.x;
    }

    // 오른쪽 대각선 2 영역일 경우
    else
    {
        Vertex.x = Src.Max.x;
    }

    // 아래쪽 영역일 경우
    if (DestCenter.y < Src.Min.y)
    {
        Vertex.y = Src.Min.y;
    }

    else
    {
        Vertex.y = Src.Max.y;
    }

    // 구해준 사각형의 꼭지점이 원 안에 들어가는지를 판단한다.
    float Dist = Vertex.Distance(DestCenter);

    if (Dist <= DestRadius)
    {
        HitPoint = Vertex;

        return true;
    }

    return false;
}

bool CCollision::CollisionOBB2DToOBB2D(
    FVector3D& HitPoint, 
    const FOBB2D& Src, const FOBB2D& Dest)
{
    FVector2D   CenterLine = Src.Center - Dest.Center;

    if (!ComputeAxisProjection(CenterLine,
        Src.Axis[EAxis::X], Src.HalfSize.x,
        Dest.Axis, Dest.HalfSize))
        return false;

    if (!ComputeAxisProjection(CenterLine,
        Src.Axis[EAxis::Y], Src.HalfSize.y,
        Dest.Axis, Dest.HalfSize))
        return false;

    if (!ComputeAxisProjection(CenterLine,
        Dest.Axis[EAxis::X], Dest.HalfSize.x,
        Src.Axis, Src.HalfSize))
        return false;

    if (!ComputeAxisProjection(CenterLine,
        Dest.Axis[EAxis::Y], Dest.HalfSize.y,
        Src.Axis, Src.HalfSize))
        return false;

    // 상자 2개를 AABB2D 정보로 만들어서 두 교집합의
    // 중점을 구한다.
    FAABB2D Hit1, Hit2;

    Hit1 = CreateAABB2D(Src);
    Hit2 = CreateAABB2D(Dest);

    FVector3D   Min, Max;
    Min.x = Hit1.Min.x > Hit2.Min.x ? Hit1.Min.x : Hit2.Min.x;
    Min.y = Hit1.Min.y > Hit2.Min.y ? Hit1.Min.y : Hit2.Min.y;

    Max.x = Hit1.Max.x < Hit2.Max.x ? Hit1.Max.x : Hit2.Max.x;
    Max.y = Hit1.Max.y < Hit2.Max.y ? Hit1.Max.y : Hit2.Max.y;

    HitPoint.x = (Min.x + Max.x) * 0.5f;
    HitPoint.y = (Min.y + Max.y) * 0.5f;

    return true;
}

bool CCollision::CollisionAABB2DToOBB2D(
    FVector3D& HitPoint, const FAABB2D& Src,
    const FOBB2D& Dest)
{
    FOBB2D  SrcOBB = CreateOBB2D(Src);

    return CollisionOBB2DToOBB2D(HitPoint, SrcOBB, Dest);
}

bool CCollision::CollisionSphere2DToOBB2D(
    FVector3D& HitPoint, const FVector3D& SrcCenter, 
    float SrcRadius, const FOBB2D& Dest)
{
    FVector2D   ConvertCenter;
    ConvertCenter.x = SrcCenter.x;
    ConvertCenter.y = SrcCenter.y;

    FVector2D   CenterLine = ConvertCenter - Dest.Center;

    FVector2D   Axis = CenterLine;
    Axis.Normalize();

    if (!ComputeAxisProjection(CenterLine,
        Axis, SrcRadius,
        Dest.Axis, Dest.HalfSize))
        return false;

    float CenterProjectionDist = 
        abs(CenterLine.Dot(Dest.Axis[EAxis::X]));

    if (CenterProjectionDist >
        SrcRadius + Dest.HalfSize.x)
        return false;

    CenterProjectionDist = 
        abs(CenterLine.Dot(Dest.Axis[EAxis::Y]));

    if (CenterProjectionDist >
        SrcRadius + Dest.HalfSize.y)
        return false;

    // 상자 2개를 AABB2D 정보로 만들어서 두 교집합의
    // 중점을 구한다.
    FAABB2D Hit1, Hit2;

    Hit1 = CreateAABB2D(ConvertCenter, SrcRadius);
    Hit2 = CreateAABB2D(Dest);

    FVector3D   Min, Max;
    Min.x = Hit1.Min.x > Hit2.Min.x ? Hit1.Min.x : Hit2.Min.x;
    Min.y = Hit1.Min.y > Hit2.Min.y ? Hit1.Min.y : Hit2.Min.y;

    Max.x = Hit1.Max.x < Hit2.Max.x ? Hit1.Max.x : Hit2.Max.x;
    Max.y = Hit1.Max.y < Hit2.Max.y ? Hit1.Max.y : Hit2.Max.y;

    HitPoint.x = (Min.x + Max.x) * 0.5f;
    HitPoint.y = (Min.y + Max.y) * 0.5f;

    return true;
}

bool CCollision::ComputeAxisProjection(
    const FVector2D& CenterLine, 
    const FVector2D& SeparationAxis,
    float AxisHalfSize, const FVector2D* DestAxis,
    const FVector2D& DestHalfSize)
{
    // 센터를 연결하는 벡터를 분리축 후보에 투영하여
    // 구간의 길이를 구한다.
    // 단, 값 비교를 위해 마이너스 값은 필요가 없으므로
    // 절대값을 이용하여 구한다.
    float CenterProjectionDist = abs(CenterLine.Dot(SeparationAxis));

    // Src와 Dest를 분리축에 투영한 구간을 구한다.
    // Src의 X축에 투영하면 Src의 투영한 구간의 길이는
    // Src의 X절반 길이와 같다.
    float DestProjectionDist =
        abs(SeparationAxis.Dot(DestAxis[EAxis::X])) * DestHalfSize.x +
        abs(SeparationAxis.Dot(DestAxis[EAxis::Y])) * DestHalfSize.y;

    if (CenterProjectionDist >
        AxisHalfSize + DestProjectionDist)
        return false;

    return true;
}

FAABB2D CCollision::CreateAABB2D(const FOBB2D& Info)
{
    FAABB2D result;

    FVector2D   Pos[4];

    Pos[0] = Info.Center - Info.Axis[0] * Info.HalfSize +
        Info.Axis[1] * Info.HalfSize;

    Pos[1] = Info.Center - Info.Axis[0] * Info.HalfSize -
        Info.Axis[1] * Info.HalfSize;

    Pos[2] = Info.Center + Info.Axis[0] * Info.HalfSize +
        Info.Axis[1] * Info.HalfSize;

    Pos[3] = Info.Center + Info.Axis[0] * Info.HalfSize -
        Info.Axis[1] * Info.HalfSize;

    result.Min.x = Pos[0].x;
    result.Min.y = Pos[0].y;

    result.Max.x = Pos[0].x;
    result.Max.y = Pos[0].y;

    for (int i = 1; i < 4; ++i)
    {
        result.Min.x = result.Min.x > Pos[i].x ? Pos[i].x : result.Min.x;
        result.Min.y = result.Min.y > Pos[i].y ? Pos[i].y : result.Min.y;

        result.Max.x = result.Max.x < Pos[i].x ? Pos[i].x : result.Max.x;
        result.Max.y = result.Max.y < Pos[i].y ? Pos[i].y : result.Max.y;
    }

    return result;
}

FAABB2D CCollision::CreateAABB2D(const FVector2D& Center, 
    float Radius)
{
    FAABB2D result;
    
    result.Min = Center - Radius;
    result.Max = Center + Radius;

    return result;
}

FOBB2D CCollision::CreateOBB2D(const FAABB2D& Info)
{
    FOBB2D  result;

    result.Center = (Info.Min + Info.Max) * 0.5f;

    result.Axis[EAxis::X].x = 1.f;
    result.Axis[EAxis::X].y = 0.f;

    result.Axis[EAxis::Y].x = 0.f;
    result.Axis[EAxis::Y].y = 1.f;

    result.HalfSize = (Info.Max - Info.Min) * 0.5f;

    return result;
}
