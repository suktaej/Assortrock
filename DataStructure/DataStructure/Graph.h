#pragma once
#include "Array_def.h"
#include "Stack_def.h"
#include "Queue_def.h"

template<typename T>
class CGraphEdge
{
	template<typename T>
	friend class CGraphNode;
	template<typename T>
	friend class CGraph;
private:
	CGraphEdge() {}
	~CGraphEdge() {}
private:
	//간선의 도착노드 정보
	CGraphNode<T>* m_Node = nullptr;
	//비용 정보
	int m_Cost = 0;
};

template<typename T>
class CGraphNode
{
	template<typename T>
	friend class CGraph;
private:
	CGraphNode() {}
	~CGraphNode() 
	{
		int Size = m_EdgeArray.size();

		for (int i = 0;i < Size;i++)
			delete m_EdgeArray[i];
	}
private:
	//노드가 가지는 정보
	T m_Data;
	//노드가 가지는 엣지(배열)
	CArray<CGraphEdge<T>*> m_EdgeArray;
	//탐색 시 방문확인 플래그
	bool m_Visit = false;
};

enum class EGrpahType
{
	Dir,
	NonDir
};


template<typename T>
class CGraph
{
private:
	typedef CGraphNode<T> NODE;
	typedef CGraphEdge<T> EDGE;
public:
	CGraph() {}
	~CGraph() 
	{
		int Size = m_NodeArray.size();
		
		for (int i = 0;i < Size;i++)
			delete m_NodeArray[i];
	}
private:
	CArray<CGraphNode<T>*> m_NodeArray;
	EGrpahType m_Type = EGrpahType::NonDir;
public:
	void AddData(const T& Data)
	{
		NODE* Node = new NODE;
		Node->m_Data = Data;
		m_NodeArray.push_back(Node);
	}
	void AddEdge(const T& Src, const T& Dest)
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
		//노드가 가지는 변수는 엣지배열
		SrcNode->m_EdgeArray.push_back(Edge);
	
		if (m_Type == EGrpahType::NonDir)
		{
			EDGE* revEdge = new EDGE;
			revEdge->m_Node = SrcNode;
			DestNode->m_EdgeArray.push_back(revEdge);
		}
	}

	void DFS(const T& Start, void (*Func)(const T&))
	{
		NODE* StartNode = nullptr;
		CStackList<NODE*> Stack;
		
		int Size = m_NodeArray.size();

		for (int i = 0;i < Size;i++)
		{
			if (m_NodeArray[i]->m_Data == Start)
				StartNode = m_NodeArray[i];

			m_NodeArray[i]->m_Visit = false;
		}

		if (!StartNode)
			return;

		Stack.push(StartNode);
		StartNode->m_Visit = true;

		while (!Stack.empty())
		{
			NODE* Node = Stack.pop();
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
