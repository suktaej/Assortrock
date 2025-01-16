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
    //레이아웃, 번호 등을 지정하기 위한 구조체
    //구조체 하나 당 
    //정점 구조는 원하는 대로 작성 가능
    //입력 레이아웃 구성 시 정적배열로 처리 불가(동적배열)
    ID3D11InputLayout* m_InputLayout = nullptr;

    //레지스터 지정을 위한 구조체
    //레이아웃 요소 1개를 표현
    std::vector<D3D11_INPUT_ELEMENT_DESC> m_vecDesc;

    unsigned int m_InputLayoutSize = 0;

    // VertexShader 객체.
    ID3D11VertexShader* m_VS = nullptr;
    // VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
    ID3DBlob* m_VSBlob = nullptr;

    // PixelShader 객체.
    ID3D11PixelShader* m_PS = nullptr;
    ID3DBlob* m_PSBlob = nullptr;

    // HullShader 객체.
    ID3D11HullShader* m_HS = nullptr;
    ID3DBlob* m_HSBlob = nullptr;

    // DomainShader 객체.
    ID3D11DomainShader* m_DS = nullptr;
    ID3DBlob* m_DSBlob = nullptr;

    // GeometryShader 객체.
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

