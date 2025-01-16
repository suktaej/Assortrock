#pragma once
#include "Shader.h"
class CGraphicShader abstract :
    public CShader
{
protected:
    CGraphicShader();
    virtual ~CGraphicShader();
private:
    //���̾ƿ�, ��ȣ ���� �����ϱ� ���� ����ü
    //����ü �ϳ� �� 
    //���� ������ ���ϴ� ��� �ۼ� ����
    //�Է� ���̾ƿ� ���� �� �����迭�� ó�� �Ұ�(�����迭)
    
    ID3D11InputLayout* mInputLayout = nullptr;
    //���̾ƿ� ��� 1���� ǥ��
    std::vector<D3D11_INPUT_ELEMENT_DESC> mvecDesc;
public:
    virtual bool Init() override;
    virtual void SetShader() final;
public:
};

