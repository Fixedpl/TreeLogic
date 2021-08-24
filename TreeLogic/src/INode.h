#pragma once
#include <cstdint>
#include <string>

#include "TreeIterator.h"


template <typename T>
class IAddingStrategy;


template <typename T>
class INode
{
protected:

	uint32_t m_id;

	T m_data;

	IAddingStrategy<T>* m_adding_strategy;

public:

	INode<T>* m_father = nullptr;

public:

	virtual ~INode() {}

	virtual void add(INode<T>* to_add) = 0;

	virtual void remove() = 0;

	virtual void search(const T& data, TreeIterator<INode<T>*>* treeIterator) = 0;

	virtual uint32_t sonsCount() = 0;

	virtual uint32_t subtreeNodeCount() = 0;

	inline uint32_t getId() { return m_id; }

	inline T getData() { return m_data; }

	void setData(const T& data) { m_data = data; }

	virtual void print(const std::string& prefix) = 0;

	virtual void setAddingStrategy(IAddingStrategy<T>* adding_strategy) = 0;

};
