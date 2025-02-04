#pragma once
#include "../../GameInfo.h"
//Asset Manager�� �����Ǿ� ����
class CMeshManager
{
	friend class CAssetManager;
//����Ŵ����̹Ƿ� ��ü������ ����
private:
	CMeshManager();
	~CMeshManager();
private:
	//Ű �ߺ��� ������ ����
	//ordered_multimap : �ߺ� ���
	//unordered map�� hashmap
	std::unordered_map<std::string, CSharedPtr<class CMesh>> m_MeshMap;
public:
	bool CreateMesh(
		const std::string& Name,
		void* VertexData,
		int Size,			//���ؽ� �������� ũ��(byte)
		int Count,			//���ؽ� ������ ����
		D3D11_USAGE VertexUsage,	//������ ������
		D3D11_PRIMITIVE_TOPOLOGY Primitive,	//������ �� �⺻����
		void* IndexData = nullptr,
		int IndexSize = 0,
		int IndexCount= 0,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);

	bool Init();
};

