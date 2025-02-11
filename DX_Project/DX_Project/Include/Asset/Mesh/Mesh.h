#pragma once
#include "../Asset.h"

// Mesh�� ������ ������ vertex, index, shader, material
// slot���� index�� �����Ͽ� ���ϴ� ����� ����
// ���ÿ� material ���� ���� slot���� �����Ͽ� ����
struct FMeshSlot
{
    FIndexBuffer IndexBuffer;
    //CSharedPtr<class CMaterial> Material;
};

class CMesh abstract :
    public CAsset
{
public:
    CMesh();
    virtual ~CMesh();

protected:
    FVertexBuffer mVertexBuffer;
/*
    ID3D11Buffer* Buffer = nullptr;
    int	Size = 0;
    int	Count = 0;
    void* Data = nullptr;
*/
    std::vector<FMeshSlot*> mMeshSlot;
    D3D11_PRIMITIVE_TOPOLOGY mPrimitive;

public:
    //�Ž� ������ �޾ƿ� Mesh Ŭ���� ���ڿ� �Ҵ�
	virtual bool CreateMesh(
		void* VertexData,	//Vertex ����
		int Size,			//Vertex ũ�� sizeof("TYPE")
		int Count,			//Vertex ���� 
		D3D11_USAGE VertexUsage,    //�޸� ������
		D3D11_PRIMITIVE_TOPOLOGY Primitive, //������ ���� ������ ����
		void* IndexData = nullptr,  //Index ����
		int IndexSize = 0,          
		int IndexCount = 0,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,  //�ԷµǴ� ������
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	bool CreateBuffer(
		ID3D11Buffer** Buffer,  //������ ����
		D3D11_BIND_FLAG Flag,   //������ Ÿ��
		void* Data,             //�Է��� ������
		int Size,
		int Count,
		D3D11_USAGE Usage);

/*
    enum D3D11_USAGE
    {
        //�⺻����(���� �޸𸮿� ����)
        //���� �޸𸮿� ����� ������ lock �� unlock�ϴ� ���
        D3D11_USAGE_DEFAULT	= 0,
        //���� �޸𸮿� ����� ������ lock���� ����
        //�ٲ� ���� ���� �����̹Ƿ� �ӵ����� ����
        D3D11_USAGE_IMMUTABLE	= 1,
        //���� �޸𸮿� ������ ���� �� ����
        //������ ����� ������ ������ �ý��� �޸𸮿� ����
        //���� �� �ý��� �޸𸮿� �ִ� ������ ���
        //����� ������ ������ �ʿ��� ��� ���
        //��ƼŬ ��� ���
        D3D11_USAGE_DYNAMIC	= 2,
        //���� �޸𸮰� �ƴ� �ý��� �޸𸮿� ����
        //���� ���� ����(��� X)
        D3D11_USAGE_STAGING	= 3
    } 	D3D11_USAGE;

*/
public:
    //slot ����� ���� ��ȯ
    int GetSlotCount()  const { return (int)mMeshSlot.size(); }
    // mMeshSlot�� vector�̹Ƿ� Random Access ����
    // Index���� ���� Slot�� ��ҿ� ������ ���� ��ȯ
    const FMeshSlot* GetSlot(int SlotIndex) const { return mMeshSlot[SlotIndex]; }
/*
public:
    void SetMaterial(int SlotIndex, const std::string& Name);
    void SetMaterial(int SlotIndex, class CMaterial* Material);
public:
    virtual void Render();
    virtual void Render(int SlotIndex);
*/
};
