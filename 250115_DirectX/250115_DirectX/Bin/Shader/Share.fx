struct PS_Output_Single
{
    //float 타입 4개의 벡터
    //SV_TARGET을 하면 뒤의 0이 생략
    //: Sementic(시멘틱), 출력 레지스터에 sv_target 0번 레지스터에 Color값을 넣는다는 의미
    float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix gmatWorld;
    matrix gmatView;
    matrix gmatProj;
    matrix gmatWV;
    matrix gmatWVP;
}