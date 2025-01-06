#pragma once
#include "Array.h"
#include "Queue.h"
#include "Stack.h"

template <typename T>
class CEdge
{
	template<typename T>
	friend class CGraphNode;
	template<typename T>
	friend class CGraph;

private:
	CEdge()
	{
	}
	~CEdge()
	{
	}
private:
	CGraphNode<T>* m_Node = nullptr;
	int m_Cost = 0;
};

template<typename T>
class CGraphNode
{
	template<typename T>
	friend class CGraph;

private:
	CGraphNode()
	{
	}
	~CGraphNode()
	{
		int Size = m_EdgeArray.size();

		for (int i = 0; i < Size;i++)
			delete m_EdgeArray[i];
	}
private:
	T m_Data;
	bool m_Visit = false;
	CArray<CEdge<T>*> m_EdgeArray;
};

enum class EGraphType
{
	Dir,
	NonDir
};
//그래프 타입(방향, 무방향)

template <typename T>
class CGraph
{
public:
	CGraph()
	{

	}
	~CGraph()
	{
		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
			delete m_NodeArray[i];
	}
private:
	CArray<CGraphNode<T>*> m_NodeArray;
	EGraphType m_Type = EGraphType::NonDir;
public:
	void AddData(const T& Data)
	{
		CGraphNode<T>* Node = new CGraphNode<T>;
		Node->m_Data = Data;
		m_NodeArray.push_back(Node);
	}

	void AddEdge(const T& Src, const T& Dest)
	{
		CGraphNode<T>* SrcNode = nullptr;
		CGraphNode<T>* DestNode = nullptr;
		//무방향일 경우 양쪽 모두 연결
		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
		{
			if (m_NodeArray[i]->m_Data == Src)
				SrcNode = m_NodeArray[i];
			else if (m_NodeArray[i]->m_Data == Dest)
				DestNode = m_NodeArray[i];
	
			//노드의 시작지점과 도착지점 모두 발견 시 브레이크
			if (SrcNode && DestNode)
				break;
		}
		//둘 중 하나라도 없다면 종료
		if (!SrcNode || !DestNode)
			return;

		CEdge<T>* Edge = new CEdge<T>;
		Edge->m_Node = DestNode;
		SrcNode->m_EdgeArray.push_back(Edge);

		//양방향일 경우 도착지점에도 시작지점을 간선에 추가
		if (EGraphType::NonDir == m_Type)
		{
			CEdge<T>* Edge = new CEdge<T>;
			Edge->m_Node = SrcNode;
			DestNode->m_EdgeArray.push_back(Edge);
		}
	}

	//넓이우선탐색
	//출력을 위해 함수포인터를 인자로 받아옴
	void BFS(const T& Start, void (*Func)(const T&))
	{
		CGraphNode<T>* StartNode = nullptr;
		CQueue<CGraphNode<T>*> Queue;

		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
		{
			if (m_NodeArray[i]->m_Data == Start)
				StartNode = m_NodeArray[i];

			m_NodeArray[i]->m_Visit = false; //모든 방문 false
		}

		if (!StartNode)
			return;

		Queue.push(StartNode);
		StartNode->m_Visit = true;

		while (!Queue.empty())
		{
			CGraphNode<T>* Node = Queue.pop();
			int EdgeSize = Node->m_EdgeArray.size();

			for (int i = 0;i < EdgeSize;i++)
			{
				if (!Node->m_EdgeArray[i]->m_Node->m_Visit)
				{
					Queue.push(Node->m_EdgeArray[i]->m_Node);
					Node->m_EdgeArray[i]->m_Node->m_Visit = true;
				}
			}
			Func(Node->m_Data);
		}
	}

	void SetGraphType(EGraphType Type) { m_Type = Type; }

	void DFS(const T& Start, void (*Func)(const T&))
	{
		CGraphNode<T>* StartNode = nullptr;
		CStackList<CGraphNode<T>*> Stack;

		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
		{
			if (m_NodeArray[i]->m_Data == Start)
				StartNode = m_NodeArray[i];

			m_NodeArray[i]->m_Visit = false; //모든 방문 false
		}

		if (!StartNode)
			return;
		
		Stack.push(StartNode);
		StartNode->m_Visit = true;

		while (!Stack.empty())
		{
			CGraphNode<T>* Node = Stack.pop();
			int EdgeSize = Node->m_EdgeArray.size();

			for (int i = 0;i < EdgeSize;i++)
			{
				if (!Node->m_EdgeArray[i]->m_Node->m_Visit)
				{
					Stack.push(Node->m_EdgeArray[i]->m_Node);
					Node->m_EdgeArray[i]->m_Node->m_Visit = true;
				}
			}
			Func(Node->m_Data);
		}
	}
};
