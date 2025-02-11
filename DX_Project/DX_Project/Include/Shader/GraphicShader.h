#pragma once

#include "Shader.h"

class CGraphicShader abstract :
    public CShader
{
    friend class CShaderManager;

protected:
    CGraphicShader();
    virtual ~CGraphicShader();

private:
	//입력레이아웃
	//레이아웃, 번호 등을 지정하기 위한 구조체
    //내가 출력하려는 메쉬가 쉐이더에서 입력받는 정점 정보가 어떻게 구성되어있는지 

    // 출력하려는 쉐이더에서 입력구조체에 들어가는 정보랑 
    // 내가 메쉬를 만들 때 사용하는 구조체가 매치되도록 
    // 구현한 다음 동일한 형태의 입력 레이아웃을 생성한다
    
    //vertex buffer에 저장된 data가 shader에 어떻게 해석되는지 결정
    ID3D11InputLayout* mInputLayout = nullptr;

    //입력 레잉아웃을 정의할 때 사용하는 구조체
    //배열로 선언하여 여러개의 입력요소를 정의
    // QUE : 배열로 선언하는 이유
    std::vector<D3D11_INPUT_ELEMENT_DESC>   mvecDesc;
/*
typedef struct D3D11_INPUT_ELEMENT_DESC {
    LPCSTR SemanticName;  // 의미(Semantic) 이름 (예: "POSITION", "COLOR")
    UINT SemanticIndex;   // 의미 인덱스 (예: POSITION0, POSITION1)
    DXGI_FORMAT Format;   // 데이터 형식 (예: DXGI_FORMAT_R32G32B32_FLOAT)
    UINT InputSlot;       // 입력 슬롯 (버퍼가 여러 개일 때 구분)
    UINT AlignedByteOffset; // 정점 데이터의 바이트 오프셋
    D3D11_INPUT_CLASSIFICATION InputSlotClass; // 데이터가 정점 데이터인지 인스턴스 데이터인지 구분
    UINT InstanceDataStepRate; // 인스턴스 렌더링에서 데이터 변경 빈도 (보통 0)
} D3D11_INPUT_ELEMENT_DESC;
*/
    unsigned int    mInputLayoutSize = 0;

    // VertexShader 객체
    // GPU에서 실행될 프로그램(쉐이더 코드)를 담고있는 역할
    // HLSL code가 D3DCompile()로 compile 된 후에 생성
    ID3D11VertexShader* mVS = nullptr;

    // VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
    ID3DBlob* mVSBlob = nullptr;

    // PixelShader 객체.
    ID3D11PixelShader* mPS = nullptr;

    // PixelShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
    ID3DBlob* mPSBlob = nullptr;

    // HullShader 객체.
    ID3D11HullShader* mHS = nullptr;

    // HullShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
    ID3DBlob* mHSBlob = nullptr;

    // DomainShader 객체.
    ID3D11DomainShader* mDS = nullptr;

    // DomainShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
    ID3DBlob* mDSBlob = nullptr;

    // GeometryShader 객체.
    ID3D11GeometryShader* mGS = nullptr;

    // GeometryShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
    ID3DBlob* mGSBlob = nullptr;

public:
    virtual bool Init();
    virtual void SetShader() final;

public:
    void AddInputLayoutDesc(const char* Semantic, unsigned int SemanticIndex, DXGI_FORMAT Fmt, unsigned int InputSlot, unsigned int Size, D3D11_INPUT_CLASSIFICATION InputSlotClass, unsigned int InstanceDataStepRate);
    bool CreateInputLayout();
    bool LoadVertexShader(const char* EntryName, const TCHAR* FileName);
    bool LoadPixelShader(const char* EntryName, const TCHAR* FileName);
    bool LoadHullShader(const char* EntryName, const TCHAR* FileName);
    bool LoadDomainShader(const char* EntryName, const TCHAR* FileName);
    bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName);
};

