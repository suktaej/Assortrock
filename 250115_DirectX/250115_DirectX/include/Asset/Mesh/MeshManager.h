#pragma once
#include "../../GameInfo.h"
//Asset Manager가 생성되어 있음
class CMeshManager
{
	friend class CAssetManager;
//서브매니저이므로 객체생성을 방지
private:
	CMeshManager();
	~CMeshManager();
private:
	//키 중복이 허용되지 않음
	//ordered_multimap : 중복 허용
	//unordered map은 hashmap
	std::unordered_map<std::string, CSharedPtr<class CMesh>> m_MeshMap;
public:
	bool CreateMesh(
		const std::string& Name,
		void* VertexData,
		int Size,			//버텍스 데이터의 크기(byte)
		int Count,			//버텍스 데이터 개수
		D3D11_USAGE VertexUsage,	//버퍼의 저장방식
		D3D11_PRIMITIVE_TOPOLOGY Primitive,	//렌더링 시 기본도형
		void* IndexData = nullptr,
		int IndexSize = 0,
		int IndexCount= 0,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);

	bool Init();
};

