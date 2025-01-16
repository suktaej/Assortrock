#pragma once
#include "GraphicShader.h"
#pragma once
#include "GraphicShader.h"
class CColorMeshShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CColorMeshShader();
    ~CColorMeshShader() override;

public:
    bool Init() override;
};

