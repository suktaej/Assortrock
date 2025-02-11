struct PS_Output_Single
{
    //float 타입 4개의 벡터
    //SV_TARGET을 하면 뒤의 0이 생략
    //: Sementic(시멘틱), 출력 레지스터에 sv_target 0번 레지스터에 Color값을 넣는다는 의미
    float4 Color : SV_TARGET;
};

//Prefix
//Constant Buffer(상수버퍼) :b
//Texture : t
//Sampler : s
//Resource : u
//Constants : c
//사용 레지스터 직접 지정
cbuffer Transform : register(b0)
{
    matrix gmatWorld;
    matrix gmatView;
    matrix gmatProj;
    matrix gmatWV;
    matrix gmatWVP;
}