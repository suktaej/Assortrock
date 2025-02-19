#include "Widget.h"
#include "../Shader/ShaderManager.h"
#include "../Shader/Shader.h"

CWidget::CWidget()
{
}

CWidget::~CWidget()
{
}

void CWidget::SetShader(const std::string& Name)
{
    mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CWidget::SetShader(CShader* Shader)
{
    mShader = Shader;
}

bool CWidget::Init()
{
    return true;
}

void CWidget::Update(float DeltaTime)
{
}

void CWidget::Render()
{
}

bool CWidget::CollisionMouse(const FVector2D& MousePos)
{
    if (mRotation == 0.f || mRotation == 360.f)
    {
        // 사각형 정보를 만든다.
        FVector2D   Min = mPos - mSize * mPivot;
        FVector2D   Max = Min + mSize;

        if (MousePos.x < Min.x)
            return false;

        else if (MousePos.x > Max.x)
            return false;

        else if (MousePos.y < Min.y)
            return false;

        else if (MousePos.y > Max.y)
            return false;

        return true;
    }

    // 회전이 있을 경우 OBB로 처리한다.
    FVector3D   OriginAxis[2];
    FVector2D   Axis[2];
    FVector2D   HalfSize = mSize * 0.5f;
    FVector2D   Center = mPos - mSize * mPivot + HalfSize;

    FMatrix matRot;
    matRot.RotationZ(mRotation);

    OriginAxis[0] = FVector3D::Axis[EAxis::X];
    OriginAxis[1] = FVector3D::Axis[EAxis::Y];

    OriginAxis[0] = OriginAxis[0].TransformNormal(matRot);
    OriginAxis[1] = OriginAxis[1].TransformNormal(matRot);

    Axis[0].x = OriginAxis[0].x;
    Axis[0].y = OriginAxis[0].y;
    Axis[1].x = OriginAxis[1].x;
    Axis[1].y = OriginAxis[1].y;

    Axis[0].Normalize();
    Axis[1].Normalize();

    // 위에서 준비한 OBB 정보를 이용해서 마우스 위치와 충돌처리를 한다.
    // 분리축 후보는 상자 축의 X, Y 축이다.
    FVector2D   CenterLine = Center - MousePos;

    float CenterProjectionDist = abs(CenterLine.Dot(Axis[0]));

    if (CenterProjectionDist > HalfSize.x)
        return false;

    CenterProjectionDist = abs(CenterLine.Dot(Axis[1]));

    if (CenterProjectionDist > HalfSize.y)
        return false;

    return true;
}
