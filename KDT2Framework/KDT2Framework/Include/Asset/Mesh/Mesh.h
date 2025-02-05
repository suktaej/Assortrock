#pragma once

#include "../Asset.h"

struct FMeshSlot
{
    FIndexBuffer    IndexBuffer;
};

class CMesh abstract :
    public CAsset
{
public:
    CMesh();
    virtual ~CMesh();

protected:
    FVertexBuffer       mVertexBuffer;
    std::vector<FMeshSlot*> mMeshSlot;
    D3D11_PRIMITIVE_TOPOLOGY    mPrimitive;

public:
    virtual bool CreateMesh(void* VertexData, int Size, int Count,
        D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
        void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0,
        DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

public:
    bool CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, 
        int Size, int Count, D3D11_USAGE Usage);


public:
    void Render();
};

