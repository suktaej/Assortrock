#include "Share.fx"

struct VS_Input_Color
{
    float3 Pos : POSITION;  //position 0�� reg
    float4 Color : COLOR;   //color 0�� reg
};

struct VS_Output_Color
{
    //������ȯ �� w�� view�� z�� ����
    //���� ���������� w�� ����
    //4���� �� �ʿ�
    float4 Pos : SV_POSITION;  //Output�� ���� �� ���常 �����ϵ��� SV
    float4 Color : COLOR;
};

//vertex shader�� ȣ��
//VS_Input_Color���� �������� ������ �����Ƿ� �������͸� ���ڷ� �޾ƿ�
VS_Output_Color ColorMeshVS(VS_Input_Color input)
{
    //0�� ����ü Ÿ������ ����ȯ�Ͽ� ����
    //��� ����� 0���� �ʱ�ȭ
    VS_Output_Color output = (VS_Output_Color)0;
    
    //output.Pos�� x,y,z�� input.Pos�� x,y,z ����
    //w�� 1.f ����, w���� ���� ���ٰ��� ����
    //(x/w, y/w)�� �����ϱ� ����
    //inputPos�� ���� ��ǥ
    //����� ���(���Ҽ�)����
    //output.Pos = float4(input.Pos, 1.f);
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
    output.Color = input.Color;

    return output;
}
//������ �ø�ƽ�� COLOR 0�� ���������� ���� Color�� �������� ���
//PS_Output_Single ColorMeshPS(float4 Color: COLOR)
PS_Output_Single ColorMeshPS(VS_Output_Color input)
{
    PS_Output_Single output = (PS_Output_Single)0;
    output.Color = input.Color;
    
    return output;
}