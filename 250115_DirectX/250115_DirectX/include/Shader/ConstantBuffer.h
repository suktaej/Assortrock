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
    //� ���̴��� ������۸� �Ѱ��� ������ �۾�
    bool Init(int Size, int Register, int ShaderBufferType);
};

