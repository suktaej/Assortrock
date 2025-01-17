struct PS_Output_Single
{
    //float 타입 4개의 벡터
    //SV_TARGET을 하면 뒤의 0이 생략
    //: 시멘틱, 출력 레지스터에 sv_target 0번 레지스터에 입력
    float4 Color : SV_TARGET;
};