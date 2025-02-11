#include "Vector4D.h"

FVector4D FVector4D::Black = { 0.f, 0.f, 0.f, 1.f };
FVector4D FVector4D::White = { 1.f, 1.f, 1.f, 1.f };
FVector4D FVector4D::Red = { 1.f, 0.f, 0.f, 1.f };
FVector4D FVector4D::Green= { 0.f, 1.f, 0.f, 1.f };
FVector4D FVector4D::Blue= { 0.f, 0.f, 1.f, 1.f };

//4차원 벡터의 경우 색상으로 활용(RGBA)