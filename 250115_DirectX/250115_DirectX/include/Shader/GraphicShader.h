#pragma once
#include "Shader.h"
class CGraphicShader abstract :
    public CShader
{
    friend class CShaderManager;

protected:
    CGraphicShader();
    ~CGraphicShader() override;
private:
    //���̾ƿ�, ��ȣ ���� �����ϱ� ���� ����ü
    //����ü �ϳ� �� 
    //���� ������ ���ϴ� ��� �ۼ� ����
    //�Է� ���̾ƿ� ���� �� �����迭�� ó�� �Ұ�(�����迭)
    ID3D11InputLayout* m_InputLayout = nullptr;

    //�������� ������ ���� ����ü
    //���̾ƿ� ��� 1���� ǥ��
    std::vector<D3D11_INPUT_ELEMENT_DESC> m_vecDesc;

    unsigned int m_InputLayoutSize = 0;

    // VertexShader ��ü.
    ID3D11VertexShader* m_VS = nullptr;
    // VertexShader �ڵ带 �������ϰ� ����Ʈ �ڵ带 �����ϱ� ���� ����
    ID3DBlob* m_VSBlob = nullptr;

    // PixelShader ��ü.
    ID3D11PixelShader* m_PS = nullptr;
    ID3DBlob* m_PSBlob = nullptr;

    // HullShader ��ü.
    ID3D11HullShader* m_HS = nullptr;
    ID3DBlob* m_HSBlob = nullptr;

    // DomainShader ��ü.
    ID3D11DomainShader* m_DS = nullptr;
    ID3DBlob* m_DSBlob = nullptr;

    // GeometryShader ��ü.
    ID3D11GeometryShader* m_GS = nullptr;
    ID3DBlob* m_GSBlob = nullptr;
public:
    bool Init() override;
    void SetShader() final;
public:
    void AddInputLayoutDesc(
        const char* Semantic,
        unsigned int SemanticIndex,
        DXGI_FORMAT Fmt,
        unsigned int InputSlot,
        unsigned int Size,
        D3D11_INPUT_CLASSIFICATION InputSlotClass,
        unsigned int InstanceDataStepRate
    );
    bool CreateInputLayout();
    bool LoadVertexShader(const char* EntryName, const TCHAR* FileName);
    bool LoadPixelShader(const char* EntryName, const TCHAR* FileName);
    bool LoadHullShader(const char* EntryName, const TCHAR* FileName);
    bool LoadDomainShader(const char* EntryName, const TCHAR* FileName);
    bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName);
};

