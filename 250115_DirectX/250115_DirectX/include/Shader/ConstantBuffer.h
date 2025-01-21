#pragma once
#include "../Share/Object.h"
#include "CBufferContainer.h"

class CConstantBuffer :
    public CObject
{
    friend class CShaderManager;
private:
    CConstantBuffer();
    ~CConstantBuffer();
private:
    //상수버퍼 역시 버퍼로 생성
    //용도만 상수 버퍼
    ID3D11Buffer* m_Buffer;
    int m_Size;
    int m_Register = 0;
    //쉐이더 버퍼 타입
    //GameInfo내 구조체 EShaderBufferType
    int m_ShaderBufferType = 0;
public:
    //어떤 쉐이더에 상수버퍼를 넘겨줄 것인지 작업
    bool Init(int Size, int Register, int ShaderBufferType);
};

