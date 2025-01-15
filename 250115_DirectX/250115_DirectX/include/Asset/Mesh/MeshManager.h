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
	std::unordered_map<std::string, CSharedPtr> m_MeshMap;
public:
	bool CreateMesh(
		const std::string& Name,
		void* VertexData,
		int Size,			//���ؽ� �������� ũ��(byte)
		int Count,			//���ؽ� ������ ����
		D3D11_USAGE VertexUsage,	//������ ������
		D3D11_PRIMITIVE_TOPOLOGY Primitive,	//������ �� �⺻����
		void* IndexData,
		int IndexSize,
		int IndexCount,
		DXGI_FORMAT Fmt,
		D3D11_USAGE IndexUsage);

	class CMesh* FindMesh(const std::string& Name);
};

