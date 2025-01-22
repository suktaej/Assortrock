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
    //������� ���� ���۷� ����
    //�뵵�� ��� ����
    ID3D11Buffer* m_Buffer;
    int m_Size = 0; //���� ũ��
    int m_Register = 0;
    //���̴� ���� Ÿ��
    //GameInfo�� ����ü EShaderBufferType
    int m_ShaderBufferType = 0;
public:
    //� ���̴��� ������۸� �Ѱ��� ������ �۾�
    bool Init(int Size, int Register, int ShaderBufferType);
    void Update(void* Data);
};

