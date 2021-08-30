#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

#include "INode.h"



template <typename T>
class IAddingStrategy;

template <typename T>
class Node : public INode<T>
{
protected:

	std::vector<INode<T>*> m_sons;

public:

	Node(const uint32_t& id, const T& data);

	void addSonPtr(INode<T>* node);

	void removeSonPtr(INode<T>* node);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	std::vector<INode<T>*> getSons();

};

#include "IAddingStrategy.h"

template <typename T>
Node<T>::Node(const uint32_t& id, const T& data)
{
	this->m_id = id;
	this->m_data = data;
}

template <typename T>
void Node<T>::addSonPtr(INode<T>* node) {
	node->m_father = this;
	m_sons.push_back(node);
}

template<typename T>
void Node<T>::removeSonPtr(INode<T>* node)
{
	m_sons.erase(std::find(m_sons.begin(), m_sons.end(), node));
}

template<typename T>
uint32_t Node<T>::sonsCount()
{
	return m_sons.size();
}

template<typename T>
uint32_t Node<T>::subtreeNodeCount()
{
	uint32_t count = 0;
	for (auto& node : m_sons) {
		count += node->subtreeNodeCount() + 1;
	}
	return count;
}

template<typename T>
std::vector<INode<T>*> Node<T>::getSons()
{
	return m_sons;
}
