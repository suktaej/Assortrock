#pragma once
#include "Shader.h"
class CComputeShader :
    public CShader
{
protected:
    CComputeShader();
    virtual ~CComputeShader();
public:
    bool Init() override;
    void SetShader() final;
};


