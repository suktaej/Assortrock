#pragma once
#include "../Share/Object.h"

class CConstantBuffer :
    public CObject
{
    friend class ShaderManager;
private:
    CConstantBuffer();
    ~CConstantBuffer();
private:
    ID3D11Buffer* m_Buffer;
    int m_Size;
    int m_Register = 0;
public:
    //어떤 쉐이더에 상수버퍼를 넘겨줄 것인지 작업
    bool Init(int Size, int Register, int ShaderBufferType);
};

