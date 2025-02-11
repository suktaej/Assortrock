#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

struct FTransformCBufferInfo
{
    FMatrix matWorld;
    FMatrix matView;
    FMatrix matProj;
    FMatrix matWV;
    FMatrix matWVP;
};

struct FMaterialCBufferInfo
{
    FVector4D BaseColor;
    float Opacity;
    int TextureWidth;
    int TextureHeight;
    float Empty;
};

struct FColliderCBufferInfo
{
    FVector4D   Color;
};
