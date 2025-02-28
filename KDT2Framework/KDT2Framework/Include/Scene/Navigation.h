#pragma once

#include "../GameInfo.h"

//A*의 상태
enum class ENavNodeType
{
	None,
	Open,
	Close
};

//8방향 이동 값
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
	//부모노드
	FNavNode* Partent = nullptr;
	//상태
	ENavNodeType NodeType = ENavNodeType::None;
	// 타일맵 정보가 갱신될 때마다 갱신되어야 하므로
	// 노드 안에서 구현하지 않고 밖에서 확인
	//ETileType TileType = ETileType::None;
	FVector2D Pos;
	FVector2D Size;
	FVector2D Center;
	int IndexX = 0;
	int IndexY = 0;
	int Index = 0;
	//최종비용(이동하며 누적된 비용)
	float ToTal= FLT_MAX;
	//휴리스틱 비용
	float Huristic = FLT_MAX;
	//노드 간 이동 비용(거리비용)
	float Dist = FLT_MAX;
	//방향으로의 직선탐색 검증
	std::list<ENodeDir> SearchDirList;
};

//비용비교용 구조체
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
	// 생성되는 전체 node의 list
	std::vector<FNavNode*> mNodeList;
	// 열린 상태의 목록
	// 이는 비용이 작은 것을 우선적으로 사용해야 함
	// 우선순위 Queue가 필요
	// std::map의 자동정렬은 유용하나 빈번한 추가삭제에 유용하지 않음
	// 인자2. 비교용 구조체를 추가하여 동작하도록 함
	// Container는 Vector를 이용
	// 인자3. 비용을 비교할 구조체 삽입
	std::priority_queue<FNavNode*,std::vector<FNavNode*>,>

	int mCountX = 0;
	int mCountY = 0;
	FVector2D mTileSize;

public:
	void SetTileMap(class CTileMapCOmponent* TileMap);
	bool Init();
	//길찾기 기능
	//탐색 결과를 반환
	//시작지점과 도착지점, 경로를 가질 list
	bool FindPath(const FVector2D& Start,
		const FVector2D& End,
		std::list<FVector2D>& PathList);

};

