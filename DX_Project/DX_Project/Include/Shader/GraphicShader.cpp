#include "GraphicShader.h"
#include "../Device.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
    SAFE_RELEASE(mInputLayout);

    SAFE_RELEASE(mVS);
    SAFE_RELEASE(mVSBlob);

    SAFE_RELEASE(mPS);
    SAFE_RELEASE(mPSBlob);

    SAFE_RELEASE(mHS);
    SAFE_RELEASE(mHSBlob);

    SAFE_RELEASE(mDS);
    SAFE_RELEASE(mDSBlob);

    SAFE_RELEASE(mGS);
    SAFE_RELEASE(mGSBlob);
}

bool CGraphicShader::Init()
{
    return true;
}

void CGraphicShader::SetShader()
{
    //Graphic Shader 변수(mVS, mPS 등)를 DX context의 setshader를 사용
    //각 쉐이더를 그래픽 파이프라인에 바인딩
    CDevice::GetInst()->GetContext()->VSSetShader(mVS, nullptr, 0);
    CDevice::GetInst()->GetContext()->PSSetShader(mPS, nullptr, 0);
    CDevice::GetInst()->GetContext()->HSSetShader(mHS, nullptr, 0);
    CDevice::GetInst()->GetContext()->DSSetShader(mDS, nullptr, 0);
    CDevice::GetInst()->GetContext()->GSSetShader(mGS, nullptr, 0);
    //입력 어셈블러 단계에서 사용할 인풋레이아웃 설정
    CDevice::GetInst()->GetContext()->IASetInputLayout(mInputLayout);
}

void CGraphicShader::AddInputLayoutDesc(
	const char* Semantic,
	unsigned int SemanticIndex,
	DXGI_FORMAT Fmt,
	unsigned int InputSlot,
	unsigned int Size,
	D3D11_INPUT_CLASSIFICATION InputSlotClass,
	unsigned int InstanceDataStepRate)
{
    D3D11_INPUT_ELEMENT_DESC    Desc = {};

    Desc.SemanticName = Semantic;
    Desc.SemanticIndex = SemanticIndex;
    Desc.Format = Fmt;
    Desc.InputSlot = InputSlot;
    Desc.InputSlotClass = InputSlotClass;
    Desc.InstanceDataStepRate = InstanceDataStepRate;
    Desc.AlignedByteOffset = mInputLayoutSize;

    mInputLayoutSize += Size;

    mvecDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{
    if (FAILED(CDevice::GetInst()->GetDevice()-> CreateInputLayout(
            &mvecDesc[0],
			(UINT)mvecDesc.size(),
			mVSBlob->GetBufferPointer(),
			mVSBlob->GetBufferSize(),
			&mInputLayout)))
        return false;

    return true;
}

bool CGraphicShader::LoadVertexShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR   FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);
    //Debug flag
    unsigned int    Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

    ID3DBlob* ErrorBlob = nullptr;

	if (FAILED(D3DCompileFromFile(
        FullPath,   //경로
		nullptr,    //배열(매크로 정의), 사용하지 않을경우 nullptr
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  //#include문을 처리하기 위한 표준 포함옵션
		EntryName,  //HLSL 진입함수 명
		"vs_5_0",   //세이더모델 버전
		Flag,       //디버그여부
		0,          
		&mVSBlob,   //컴파일 된 세이더 코드가 저장될 블롭(Buffer)
		&ErrorBlob)))   //오류메세지가 저장될 블롭
    {
#ifdef _DEBUG
        char    ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInst()->GetDevice()->CreateVertexShader(
        mVSBlob->GetBufferPointer(), //컴파일된 코드
        mVSBlob->GetBufferSize(),   //컴파일된 코드의 크기
        nullptr,    //클래스 링크(사용안함)
        &mVS)))     //생성된 세이더를 받을 변수
        return false;

    return true;
}

bool CGraphicShader::LoadPixelShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR   FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int    Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG


    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "ps_5_0", Flag, 0, &mPSBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char    ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInst()->GetDevice()->CreatePixelShader(
        mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(),
        nullptr, &mPS)))
        return false;

    return true;
}

bool CGraphicShader::LoadHullShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR   FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int    Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG


    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "hs_5_0", Flag, 0, &mHSBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char    ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateHullShader(
        mHSBlob->GetBufferPointer(), mHSBlob->GetBufferSize(),
        nullptr, &mHS)))
        return false;

    return true;
}

bool CGraphicShader::LoadDomainShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR   FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int    Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG


    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "ds_5_0", Flag, 0, &mDSBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char    ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    if (FAILED(CDevice::GetInst()->GetDevice()->CreateDomainShader(
        mDSBlob->GetBufferPointer(), mDSBlob->GetBufferSize(),
        nullptr, &mDS)))
        return false;

    return true;
}

bool CGraphicShader::LoadGeometryShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR   FullPath[MAX_PATH] = {};

    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int    Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG


    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName,
        "gs_5_0", Flag, 0, &mGSBlob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char    ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateGeometryShader(
        mGSBlob->GetBufferPointer(), mGSBlob->GetBufferSize(),
        nullptr, &mGS)))
        return false;

    return true;
}
