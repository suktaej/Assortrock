#pragma once
#include "Shader.h"
class CGraphicShader abstract :
    public CShader
{
protected:
    CGraphicShader();
    virtual ~CGraphicShader();
private:
    //레이아웃, 번호 등을 지정하기 위한 구조체
    //구조체 하나 당 
    //정점 구조는 원하는 대로 작성 가능
    //입력 레이아웃 구성 시 정적배열로 처리 불가(동적배열)
    
    ID3D11InputLayout* mInputLayout = nullptr;
    //레이아웃 요소 1개를 표현
    std::vector<D3D11_INPUT_ELEMENT_DESC> mvecDesc;
public:
    virtual bool Init() override;
    virtual void SetShader() final;
public:
};

