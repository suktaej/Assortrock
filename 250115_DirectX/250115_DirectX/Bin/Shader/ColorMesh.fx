#include "Share.fx"

struct VS_Input_Color
{
    float3 Pos : POSITION;  //position 0번 reg
    float4 Color : COLOR;   //color 0번 reg
};

struct VS_Output_Color
{
    //투영변환 시 w에 view의 z값 삽입
    //이후 내부적으로 w로 나눔
    //4개의 값 필요
    float4 Pos : SV_POSITION;  //Output을 위해 값 저장만 가능하도록 SV
    float4 Color : COLOR;
};

//vertex shader가 호출
//VS_Input_Color에서 레지스터 지정을 했으므로 레지스터를 인자로 받아옴
VS_Output_Color ColorMeshVS(VS_Input_Color input)
{
    //0을 구조체 타입으로 형변환하여 대입
    //모든 멤버가 0으로 초기화
    VS_Output_Color output = (VS_Output_Color)0;
    
    //output.Pos의 x,y,z에 input.Pos의 x,y,z 대입
    //w는 1.f 대입, w값에 따라 원근감이 변경
    //(x/w, y/w)를 진행하기 때문
    //inputPos는 로컬 좌표
    //행렬을 사용(복소수)개념
    //output.Pos = float4(input.Pos, 1.f);
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
    output.Color = input.Color;

    return output;
}
//인자의 시멘틱은 COLOR 0번 레지스터의 값을 Color로 꺼내오는 기능
//PS_Output_Single ColorMeshPS(float4 Color: COLOR)
PS_Output_Single ColorMeshPS(VS_Output_Color input)
{
    PS_Output_Single output = (PS_Output_Single)0;
    output.Color = input.Color;
    
    return output;
}