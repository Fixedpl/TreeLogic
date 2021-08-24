#pragma once
#include "TreeIterator.h"
#include "IAddingStrategy.h"

template <typename T>
class INode
{
private:

	static RandomAddingStrategy m_default;

protected:

	T m_data;

	static IAddingStrategy* m_adding_strategy;

public:

	INode<T>* m_father;

protected:

	INode() {
		m_adding_strategy = &m_default;
	}

public:

	virtual ~INode() {}

	virtual void add() = 0;

	virtual void remove() = 0;

	virtual void search(const T& data, TreeIterator<INode<T>*>* treeIterator) = 0;

	virtual uint32_t sonsCount() = 0;

	virtual uint32_t subtreeNodeCount() = 0;

	inline T getData() { return m_data; }

	void setData(const T& data) { m_data = data; }

	static void setAddingStrategy(IAddingStrategy* adding_strategy) { m_adding_strategy = adding_strategy; }
};

