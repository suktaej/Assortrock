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
//��¿� ����ϰ��� �ϴ� ������ ���������ο� ���
//���Ŀ� ���
void CGraphicShader::SetShader()
{
    CDevice::GetInst()->GetContext()->VSSetShader(m_VS, nullptr, 0);
    CDevice::GetInst()->GetContext()->PSSetShader(m_PS, nullptr, 0);
    CDevice::GetInst()->GetContext()->HSSetShader(m_HS, nullptr, 0);
    CDevice::GetInst()->GetContext()->DSSetShader(m_DS, nullptr, 0);
    CDevice::GetInst()->GetContext()->GSSetShader(m_GS, nullptr, 0);
    //�Է� ������(IA)
    //�Է� ���̾ƿ� ����
    //vertex ����ü���� ����Ʈ �� �������� ����
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
    //byte offsetó���� 
    m_InputLayoutSize += Size;

    m_vecDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateInputLayout(
        &m_vecDesc[0],                  //��ũ���� �����ּ�
        (UINT)m_vecDesc.size(),         //����
        m_VSBlob->GetBufferPointer(),   //VSBlob�� �ּ�
        m_VSBlob->GetBufferSize(),      //ũ��
        &m_InputLayout)))               //�Է� ���̾ƿ�
        return false;

    return true;
}

bool CGraphicShader::LoadVertexShader(const char* EntryName, const TCHAR* FileName)
{
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../Bin/Shader/"));  //�����ڵ� ���ڿ� ���� �Լ�
    lstrcat(FullPath, FileName);                //������� �� �����̸��� ����

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif //_DEBUG
    
    ID3DBlob* ErrorBlob = nullptr;              //���� �߻� �� Ȯ�ο�
   
    if(FAILED(D3DCompileFromFile(               //directX ���Ϸκ��� ������
        FullPath, 
        nullptr,                                //��ũ��
        D3D_COMPILE_STANDARD_FILE_INCLUDE,      //ǥ������ include
        EntryName,                              //�Լ� �̸�
        "vs_5_0",                               //Ÿ���� ����
        Flag,                                   
        0,
        &m_VSBlob,                              //�޾ƿ� ����Ʈ�ڵ尡 �����ϵǾ� ���ۿ� ����
        &ErrorBlob
        )))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText,(const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);          //���â ���ڿ� ����Լ�
#endif //_DEBUG
        return false;
    }
    // m_VSBlob->GetBufferPointer() : �����ϵ� �ڵ�
    // m_VSBlob->GetBufferSize() : �����ϵ� �ڵ��� ũ��
    // ���� �� ���̴� ��ü�� ����
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateVertexShader(
        m_VSBlob->GetBufferPointer(),           //����Ʈ �ڵ��� �����ּ�
        m_VSBlob->GetBufferSize(),              //�����ϵ� �ڵ��� ����
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
