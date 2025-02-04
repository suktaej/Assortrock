#include "Collision.h"
#include "Component/ColliderAABB2D.h"

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint,
    CColliderAABB2D* Src, CColliderAABB2D* Dest)
{
    if(CollisionAABB2DToAABB2D(HitPoint, Src->GetBox(), 
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
