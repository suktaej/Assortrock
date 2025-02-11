

struct PS_Output_Single
{
    // SV_TARGET을 하면 뒤에 0이 생략된다.
    float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix gmatWorld;
    matrix gmatView;
    matrix gmatProj;
    matrix gmatWV;
    matrix gmatWVP;
};

cbuffer Material : register(b1)
{
    float4 gMtrlBaseColor;
    float gMtrlOpacity;
    int gMtrlTextureWidth;
    int gMtrlTextureHeight;
    float gMtrlEmpty;
};

SamplerState gBaseSampler : register(s0);

Texture2D gBaseTexture : register(t0);
