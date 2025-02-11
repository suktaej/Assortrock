#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

//상수버퍼와 대응되는 구조체 생성
//상수버퍼 사용 시 메모리 정렬은 16byte
//byte padding 또한 16byte
struct FTransformCBufferInfo
{
    FMatrix matWorld;
    FMatrix matView;
    FMatrix matProj;
    FMatrix matWV;
    FMatrix matWVP;

    //FVector3D float12byte
    //float empty_for_padding
};
