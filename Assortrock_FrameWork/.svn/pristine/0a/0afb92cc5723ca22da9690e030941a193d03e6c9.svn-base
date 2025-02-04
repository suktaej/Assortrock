

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
