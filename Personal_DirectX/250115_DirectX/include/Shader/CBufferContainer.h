#pragma once

#include "../Vector2D.h"
#include "../Vector3D.h"
#include "../Vector4D.h"
#include "../Matrix.h"

//������ۿ� �����Ǵ� ����ü ����
//������� ��� �� �޸� ������ 16byte
//byte padding ���� 16byte
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
