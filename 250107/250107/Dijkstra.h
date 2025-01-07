#pragma once
#include "Array.h"
#include "Heap.h"
#include "Stack.h"

template <typename T>
class CDijkstraEdge
{
	template<typename T>
	friend class CDijkstraNode;
	template<typename T>
	friend class CDijkstra;

private:
	CDijkstraEdge()
	{
	}
	~CDijkstraEdge()
	{
	}
private:
	CDijkstraNode<T>* m_Node = nullptr;
	unsigned int m_Weight = 0;
	//node와 node 사이의 이동비용
};

template<typename T>
class CDijkstraNode
{
	template<typename T>
	friend class CDijkstra;
public:
	CDijkstraNode() {}
	~CDijkstraNode() 
	{
		int Size = m_EdgeArray.size();

		for (int i = 0;i < Size;i++)
			delete m_EdgeArray[i];
	}
private:
	T m_Data;
	CDijkstraNode<T>* m_PrevNode = nullptr;
	CArray<CDijkstraEdge<T>*> m_EdgeArray;
	unsigned int m_Weight = UINT_MAX;	
	//bool m_Visit = false;
	//비용의 적립값(가중치)
	//UINT_MAX = 0xffffffff : unsigned int로 표기 가능한 최대값
};

enum class EGraphType
{
	Dir,
	NonDir
};

template<typename T>
class CDijkstra
{
private:
	typedef CDijkstraNode<T> NODE;
	typedef CDijkstraEdge<T> EDGE;
public:
	CDijkstra() {}
	~CDijkstra() {}
private:
	CArray<NODE*> m_NodeArray;
	EGraphType m_Type = EGraphType::NonDir;
public:
	void AddData(const T& Data)
	{
		NODE* Node = new NODE;
		Node->m_Data = Data;
		m_NodeArray.push_back(Node);
	}

	void AddEdge(const T& Src, const T& Dest, unsigned int Weight)
	{
		NODE* SrcNode = nullptr;
		NODE* DestNode = nullptr;
		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
		{
			if (m_NodeArray[i]->m_Data == Src)
				SrcNode = m_NodeArray[i];
			else if (m_NodeArray[i]->m_Data == Dest)
				DestNode = m_NodeArray[i];

			if (SrcNode && DestNode)
				break;
		}
		if (!SrcNode || !DestNode)
			return;

		EDGE* Edge = new EDGE;
		Edge->m_Node = DestNode;
		Edge->m_Weight = Weight;

		SrcNode->m_EdgeArray.push_back(Edge);

		if (EGraphType::NonDir == m_Type)
		{
			EDGE* revEdge = new EDGE;
			revEdge->m_Node = SrcNode;
			revEdge->m_Weight = Weight;

			DestNode->m_EdgeArray.push_back(revEdge);
		}
	}

	//1번 인자는 최종 경로를 받아오기 위한 배열
	void FindPath(CArray<T>& Result,const T& Start,const T& End) 
	{
		NODE* StartNode = nullptr;
		NODE* EndNode = nullptr;

		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
		{	//시작노드 및 종료노드 탐색 및 설정
			if (m_NodeArray[i]->m_Data == Start)
				StartNode = m_NodeArray[i];
			else if (m_NodeArray[i]->m_Data == End)
				EndNode = m_NodeArray[i];
			//시작노드 초기화
			m_NodeArray[i]->m_PrevNode = nullptr;
			//m_NodeArray[i]->m_Visit = false;
			m_NodeArray[i]->m_Weight = 0xffffffff;
		}

		if (!StartNode)
			return;

		//우선순위 큐(힙)
		CHeap<NODE*> Queue;
		Queue.SetSortFunction(CDijkstra<T>::SortFunc);
		
		Queue.insert(StartNode);
		StartNode->m_Weight = 0;

		while (!Queue.empty())
		{
			NODE* Node = Queue.front();
			Queue.pop();
			int EdgeSize = Node->m_EdgeArray.size();

			for (int i = 0;i < EdgeSize;i++)
			{
				//Edge에 붙어있는 노드로 이동하기 위한 비용 계산
				//현재노드비용 + 이동하기 위한 간선비용 = 최종비용
				unsigned int Weight = Node->m_Weight + Node->m_EdgeArray[i]->m_Weight;

				//최종비용이 Edge에 붙어있는 노드의 비용보다 작다면 교체
				//각 노드의 초기 가중치는 모르는 상태(0xffffffff)로 설정되어 있음
				if (Weight < Node->m_EdgeArray[i]->m_Node->m_Weight)
				{
					Queue.insert(Node->m_EdgeArray[i]->m_Node);
					//코드 확인
					
					//if (!Node->m_EdgeArray[i]->m_Node->m_Visit)
					//	Queue.insert(Node->m_EdgeArray[i]->m_Node);
					//Node->m_EdgeArray[i]->m_Node->m_Visit = true;

					//Edge에 붙어있는 노드의 비용을 교체
					Node->m_EdgeArray[i]->m_Node->m_Weight = Weight;
					//Edge에 붙어있는 노드의 이전 노드를 Node로 지정
					Node->m_EdgeArray[i]->m_Node->m_PrevNode = Node;
				}
			}
		}
		//탐색 종료 시 경로 제거
		Result.clear();

		NODE* CurrentNode = EndNode;
		CStackList<T> Stack;
		//시작의 이전 노드는 nullptr
		//nullptr에 도달 시 종료
		while (CurrentNode)
		{
			Stack.push(CurrentNode->m_Data);
			CurrentNode = CurrentNode->m_PrevNode;
		}
		while (!Stack.empty())
		{
			T Data = Stack.pop();

			Result.push_back(Data);
		}
	}
	void SetGraphType(EGraphType Type) 
	{ m_Type = Type; }
private:
	static bool SortFunc(NODE* const& Src, NODE* const& Dest) 
	{ return Src->m_Weight > Dest->m_Weight; }
};

