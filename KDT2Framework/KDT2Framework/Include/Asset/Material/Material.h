#pragma once

#include "../Asset.h"

enum class ETextureSamplerType : unsigned char
{
    Point,
    Linear,
    Anisotropic
};

struct FMaterialTextureInfo
{
    std::string         Name;
    CSharedPtr<class CTexture>  Texture;
    ETextureSamplerType SamplerType = 
        ETextureSamplerType::Linear;
    int                 Register = 0;
    int                 ShaderBufferType = 
        (int)EShaderBufferType::Pixel;
    int                 TextureIndex = 0;
};

class CMaterial :
    public CAsset
{
    friend class CMaterialManager;

protected:
    CMaterial();
    virtual ~CMaterial();

protected:
    std::vector<FMaterialTextureInfo*> mTextureList;

public:
    void AddTexture(class CTexture* Texture);
    void AddTexture(const std::string& Name);
};

