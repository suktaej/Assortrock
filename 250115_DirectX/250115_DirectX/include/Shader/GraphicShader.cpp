#include "GraphicShader.h"
#include "../Device.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
    SAFE_RELEASE(m_InputLayout);

    SAFE_RELEASE(m_VS);
    SAFE_RELEASE(m_VSBlob);

    SAFE_RELEASE(m_PS);
    SAFE_RELEASE(m_PSBlob);

    SAFE_RELEASE(m_HS);
    SAFE_RELEASE(m_HSBlob);

    SAFE_RELEASE(m_DS);
    SAFE_RELEASE(m_DSBlob);

    SAFE_RELEASE(m_GS);
    SAFE_RELEASE(m_GSBlob);
}

bool CGraphicShader::Init()
{
    return true;
}
//출력에 사용하고자 하는 렌더링 파이프라인에 등록
//이후에 출력
void CGraphicShader::SetShader()
{
    CDevice::GetInst()->GetContext()->VSSetShader(m_VS, nullptr, 0);
    CDevice::GetInst()->GetContext()->PSSetShader(m_PS, nullptr, 0);
    CDevice::GetInst()->GetContext()->HSSetShader(m_HS, nullptr, 0);
    CDevice::GetInst()->GetContext()->DSSetShader(m_DS, nullptr, 0);
    CDevice::GetInst()->GetContext()->GSSetShader(m_GS, nullptr, 0);
    //입력 조립기(IA)
    //입력 레이아웃 지정
    //vertex 구조체에서 바이트 별 레지스터 지정
    CDevice::GetInst()->GetContext()->IASetInputLayout(m_InputLayout);
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
    D3D11_INPUT_ELEMENT_DESC Desc = {};
    Desc.SemanticName = Semantic;
    Desc.SemanticIndex = SemanticIndex;
    Desc.Format = Fmt;
    Desc.InputSlot = InputSlot;
    Desc.InputSlotClass = InputSlotClass;
    Desc.InstanceDataStepRate = InstanceDataStepRate;
    Desc.AlignedByteOffset = m_InputLayoutSize;
    //byte offset처리용 
    m_InputLayoutSize += Size;

    m_vecDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateInputLayout(
        &m_vecDesc[0],                  //디스크립션 시작주소
        (UINT)m_vecDesc.size(),         //개수
        m_VSBlob->GetBufferPointer(),   //VSBlob의 주소
        m_VSBlob->GetBufferSize(),      //크기
        &m_InputLayout)))               //입력 레이아웃
        return false;

    return true;
}

bool CGraphicShader::LoadVertexShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../Bin/Shader/"));  //유니코드 문자열 복사 함수
    lstrcat(FullPath, FileName);                //최종경로 뒤 파일이름을 삽입

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif //_DEBUG
    
    ID3DBlob* ErrorBlob = nullptr;              //에러 발생 시 확인용
   
    if(FAILED(D3DCompileFromFile(               //directX 파일로부터 컴파일
        FullPath, 
        nullptr,                                //매크로
        D3D_COMPILE_STANDARD_FILE_INCLUDE,      //표준파일 include
        EntryName,                              //함수 이름
        "vs_5_0",                               //타겟의 버전
        Flag,                                   
        0,
        &m_VSBlob,                              //받아온 바이트코드가 컴파일되어 버퍼에 저장
        &ErrorBlob
        )))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText,(const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);          //출력창 문자열 출력함수
#endif //_DEBUG
        return false;
    }
    // m_VSBlob->GetBufferPointer() : 컴파일된 코드
    // m_VSBlob->GetBufferSize() : 컴파일된 코드의 크기
    // 성공 시 쉐이더 객체를 생성
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateVertexShader(
        m_VSBlob->GetBufferPointer(),           //바이트 코드의 시작주소
        m_VSBlob->GetBufferSize(),              //컴파일된 코드의 길이
        nullptr, 
        &m_VS)))
        return false;

    return true;
}

bool CGraphicShader::LoadPixelShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif //_DEBUG

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(
        FullPath,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName,
        "ps_5_0",
        Flag,
        0,
        &m_PSBlob,
        &ErrorBlob
    )))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif //_DEBUG
        return false;
    }
    if (FAILED(CDevice::GetInst()->GetDevice()->CreatePixelShader(
        m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize(), nullptr, &m_PS)))
        return false;
    return true;
}

bool CGraphicShader::LoadHullShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif //_DEBUG

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(
        FullPath,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName,
        "hs_5_0",
        Flag,
        0,
        &m_HSBlob,
        &ErrorBlob
    )))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif //_DEBUG
        return false;
    }
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateHullShader(
        m_HSBlob->GetBufferPointer(), m_HSBlob->GetBufferSize(), nullptr, &m_HS)))
        return false;
    return true;
}

bool CGraphicShader::LoadDomainShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif //_DEBUG

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(
        FullPath,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName,
        "ds_5_0",
        Flag,
        0,
        &m_DSBlob,
        &ErrorBlob
    )))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif //_DEBUG
        return false;
    }
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateDomainShader(
        m_DSBlob->GetBufferPointer(), m_DSBlob->GetBufferSize(), nullptr, &m_DS)))
        return false;
    return true;
}

bool CGraphicShader::LoadGeometryShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../Bin/Shader/"));
    lstrcat(FullPath, FileName);

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif //_DEBUG

    ID3DBlob* ErrorBlob = nullptr;

    if (FAILED(D3DCompileFromFile(
        FullPath,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        EntryName,
        "gs_5_0",
        Flag,
        0,
        &m_GSBlob,
        &ErrorBlob
    )))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif //_DEBUG
        return false;
    }
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateGeometryShader(
        m_GSBlob->GetBufferPointer(), m_GSBlob->GetBufferSize(), nullptr, &m_GS)))
        return false;
    return true;
}
