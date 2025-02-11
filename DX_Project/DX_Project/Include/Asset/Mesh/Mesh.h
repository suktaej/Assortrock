#pragma once
#include "../Asset.h"

// Mesh가 가지는 정보는 vertex, index, shader, material
// slot으로 index를 구분하여 원하는 모양을 지정
// 동시에 material 정보 역시 slot으로 구분하여 생성
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
    //매쉬 정보를 받아와 Mesh 클래스 인자에 할당
	virtual bool CreateMesh(
		void* VertexData,	//Vertex 정보
		int Size,			//Vertex 크기 sizeof("TYPE")
		int Count,			//Vertex 개수 
		D3D11_USAGE VertexUsage,    //메모리 저장방식
		D3D11_PRIMITIVE_TOPOLOGY Primitive, //정보를 통해 생성할 도형
		void* IndexData = nullptr,  //Index 정보
		int IndexSize = 0,          
		int IndexCount = 0,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,  //입력되는 변수형
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	bool CreateBuffer(
		ID3D11Buffer** Buffer,  //생성할 버퍼
		D3D11_BIND_FLAG Flag,   //버퍼의 타입
		void* Data,             //입력할 데이터
		int Size,
		int Count,
		D3D11_USAGE Usage);

/*
    enum D3D11_USAGE
    {
        //기본버퍼(비디오 메모리에 생성)
        //비디오 메모리에 저장된 정보를 lock 후 unlock하는 방식
        D3D11_USAGE_DEFAULT	= 0,
        //비디오 메모리에 저장된 정보를 lock으로 막음
        //바뀔 일이 없는 정보이므로 속도에서 유리
        D3D11_USAGE_IMMUTABLE	= 1,
        //비디오 메모리에 공간을 생성 후 저장
        //저장한 내용과 동일한 정보를 시스템 메모리에 저장
        //갱신 시 시스템 메모리에 있는 내용을 덮어씀
        //빈번한 정보의 갱신이 필요한 경우 사용
        //파티클 등에서 사용
        D3D11_USAGE_DYNAMIC	= 2,
        //비디오 메모리가 아닌 시스템 메모리에 저장
        //갱신 전용 버퍼(출력 X)
        D3D11_USAGE_STAGING	= 3
    } 	D3D11_USAGE;

*/
public:
    //slot 요소의 개수 반환
    int GetSlotCount()  const { return (int)mMeshSlot.size(); }
    // mMeshSlot이 vector이므로 Random Access 가능
    // Index값을 통해 Slot의 요소에 접근해 값을 반환
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
