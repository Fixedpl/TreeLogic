#pragma once
#include "TreeIterator.h"

template <typename T>
class INode
{
protected:

	T m_data;

public:

	INode<T>* m_father;

protected:

	INode()
		: m_father(nullptr)
	{
	}

public:

	virtual ~INode() {}

	virtual void add(INode<T>* to_add) = 0;

	virtual void remove() = 0;

	virtual void search(const T& data, TreeIterator<INode<T>*>* treeIterator) = 0;

	virtual uint32_t sonsCount() = 0;

	virtual uint32_t subtreeNodeCount() = 0;

	inline T getData() { return m_data; }

	void setData(const T& data) { m_data = data; }

};

