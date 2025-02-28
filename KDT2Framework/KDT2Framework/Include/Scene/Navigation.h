#pragma once

#include "../GameInfo.h"

//A*�� ����
enum class ENavNodeType
{
	None,
	Open,
	Close
};

//8���� �̵� ��
enum class ENodeDir
{
	T,
	RT,
	R,
	RB,
	B,
	LB,
	L,
	LT,
	End
};

struct FNavNode
{
	//�θ���
	FNavNode* Partent = nullptr;
	//����
	ENavNodeType NodeType = ENavNodeType::None;
	// Ÿ�ϸ� ������ ���ŵ� ������ ���ŵǾ�� �ϹǷ�
	// ��� �ȿ��� �������� �ʰ� �ۿ��� Ȯ��
	//ETileType TileType = ETileType::None;
	FVector2D Pos;
	FVector2D Size;
	FVector2D Center;
	int IndexX = 0;
	int IndexY = 0;
	int Index = 0;
	//�������(�̵��ϸ� ������ ���)
	float ToTal= FLT_MAX;
	//�޸���ƽ ���
	float Huristic = FLT_MAX;
	//��� �� �̵� ���(�Ÿ����)
	float Dist = FLT_MAX;
	//���������� ����Ž�� ����
	std::list<ENodeDir> SearchDirList;
};

//���񱳿� ����ü
struct FCostCmp
{
	bool operator()(FNavNode* Src, FNavNode* Dest)
	{
		return Src->ToTal < Dest->ToTal;
	}
};

class CNavigation
{
	friend class CScene;
private:
	CNavigation();
	~CNavigation();
private:
	class CScene* mScene = nullptr;
	CSharedPtr<class CTileMap> mTileMap;
	ETileShape mShape = ETileShape::Rect;
	// �����Ǵ� ��ü node�� list
	std::vector<FNavNode*> mNodeList;
	// ���� ������ ���
	// �̴� ����� ���� ���� �켱������ ����ؾ� ��
	// �켱���� Queue�� �ʿ�
	// std::map�� �ڵ������� �����ϳ� ����� �߰������� �������� ����
	// ����2. �񱳿� ����ü�� �߰��Ͽ� �����ϵ��� ��
	// Container�� Vector�� �̿�
	// ����3. ����� ���� ����ü ����
	std::priority_queue<FNavNode*,std::vector<FNavNode*>,>

	int mCountX = 0;
	int mCountY = 0;
	FVector2D mTileSize;

public:
	void SetTileMap(class CTileMapCOmponent* TileMap);
	bool Init();
	//��ã�� ���
	//Ž�� ����� ��ȯ
	//���������� ��������, ��θ� ���� list
	bool FindPath(const FVector2D& Start,
		const FVector2D& End,
		std::list<FVector2D>& PathList);

};

