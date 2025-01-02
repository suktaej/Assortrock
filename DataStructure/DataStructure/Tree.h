#pragma once
#include <vector>

template<typename Key,typename Value>
class CNode
{
	template<typename Key,typename Value>
	friend class CTree;
public:
	CNode() {}
	~CNode() {}
private:
	Key mKey;
	Value mData;
	CNode<Key, Value>* mParent = nullptr;
	std::vector<CNode<Key, Value>*> mvecChild;
	CNode<Key, Value>** mChildArray;
};

template<typename Key,typename Value>
class CTree
{
public:
	CTree() {}
	~CTree() {}
private:
	typedef CNode<Key, Value> NODE;
private:
	NODE* mRoot = nullptr;
	int mSize = 0;
private:
public:
	void insert(const Key& pKey, const Value& Data, const Key& ParentKey)
	{
	}

};
