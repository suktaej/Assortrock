#include "Collision.h"
#include "Component/ColliderAABB2D.h"
#include "Component/ColliderSphere2D.h"

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
