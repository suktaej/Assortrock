struct PS_Output_Single
{
    //float Ÿ�� 4���� ����
    //SV_TARGET�� �ϸ� ���� 0�� ����
    //: Sementic(�ø�ƽ), ��� �������Ϳ� sv_target 0�� �������Ϳ� Color���� �ִ´ٴ� �ǹ�
    float4 Color : SV_TARGET;
};

//Prefix
//Constant Buffer(�������) :b
//Texture : t
//Sampler : s
//Resource : u
//Constants : c
//��� �������� ���� ����
cbuffer Transform : register(b0)
{
    matrix gmatWorld;
    matrix gmatView;
    matrix gmatProj;
    matrix gmatWV;
    matrix gmatWVP;
}