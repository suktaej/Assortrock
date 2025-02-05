#include "MeshManager.h"
#include "StaticMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
    FVertexColor   BoxVtx[8] =
    {
        FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),
        FVertexColor(0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f),
        FVertexColor(-0.5f, -0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f),
        FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, 1.f),

        FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 1.f, 1.f),
        FVertexColor(0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f),
        FVertexColor(-0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f),
        FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),
    };

    unsigned short  BoxIdx[36] =
    {
        0, 1, 3, 0, 3, 2,
        1, 5, 7, 1, 7, 3,
        5, 4, 6, 5, 6, 7,
        4, 0, 2, 4, 2, 6,
        4, 5, 1, 4, 1, 0,
        2, 3, 7, 2, 7, 6
    };

    if (!CreateMesh("Box", BoxVtx, sizeof(FVertexColor), 8, D3D11_USAGE_DEFAULT,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, BoxIdx,
        sizeof(unsigned short), 36, DXGI_FORMAT_R16_UINT))
        return false;

    FVertexColor    CenterRect[4] =
    {
        FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),
        FVertexColor(0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f),
        FVertexColor(-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f),
        FVertexColor(0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 1.f),
    };

    unsigned short RectIdx[6] = { 0, 1, 3, 0, 3, 2 };

    if (!CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 
        4, D3D11_USAGE_DEFAULT,
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIdx,
        sizeof(unsigned short), 6, DXGI_FORMAT_R16_UINT))
        return false;

    FVector3D    FrameCenterRect[4] =
    {
        FVector3D(-0.5f, 0.5f, 0.f),
        FVector3D(0.5f, 0.5f, 0.f),
        FVector3D(-0.5f, -0.5f, 0.f),
        FVector3D(0.5f, -0.5f, 0.f),
    };

    unsigned short FrameRectIdx[5] = { 0, 1, 3, 2, 0 };

    if (!CreateMesh("FrameCenterRect", FrameCenterRect, 
        sizeof(FVector3D),
        4, D3D11_USAGE_DEFAULT,
        D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, FrameRectIdx,
        sizeof(unsigned short), 5, DXGI_FORMAT_R16_UINT))
        return false;


    return true;
}

bool CMeshManager::CreateMesh(const std::string& Name, void* VertexData,
    int Size, int Count, D3D11_USAGE VertexUsage, 
    D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData, 
    int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
    // 이름을 이용하여 메쉬를 얻어온다.
    CMesh* Mesh = FindMesh(Name);

    // 메쉬가 이미 있을 경우 같은 이름의 중복된 메쉬가 있으므로
    // 생성을 중단한다.
    if (Mesh)
        return true;

    Mesh = new CStaticMesh;

    if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage,
        Primitive, IndexData, IndexSize, IndexCount, Fmt,
        IndexUsage))
    {
        SAFE_DELETE(Mesh);
        return false;
    }

    mMeshMap.insert(std::make_pair(Name, Mesh));

    return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
    std::unordered_map<std::string, CSharedPtr<CMesh>>::iterator   iter = mMeshMap.find(Name);

    if (iter == mMeshMap.end())
        return nullptr;

    return (CMesh*)iter->second.Get();
}
