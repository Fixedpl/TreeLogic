#pragma once
#include <vector>

#include "INode.h"
#include "TreeIterator.h"


template <typename T>
class Node : public INode<T>
{
protected:

	std::vector<INode<T>*> m_sons;

public:

	Node(const T& data);

	void add();

	void addSonPtr(INode<T>* node);

	void remove();

	void removeSonPtr(INode<T>* node);

	void search(const T& data, TreeIterator<INode<T>*>* treeIterator);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();
};

template <typename T>
Node<T>::Node(const T& data)
{
	this->m_data = data;
}

template<typename T>
void Node<T>::add()
{
	this->m_adding_strategy;
}


template <typename T>
void Node<T>::addSonPtr(INode<T>* node) {
	node->m_father = this;
	m_sons.push_back(node);
}

template <typename T>
void Node<T>::remove() {
	for (auto& node : m_sons) {
		node->remove();
		delete node;
	}
}

template<typename T>
void Node<T>::removeSonPtr(INode<T>* node)
{
	m_sons.erase(std::find(m_sons.begin(), m_sons.end(), node));
}

template<typename T>
void Node<T>::search(const T& data, TreeIterator<INode<T>*>* treeIterator)
{
	if (this->m_data == data)
		treeIterator->add(this);

	for (auto& node : m_sons) {
		node->search(data, treeIterator);
	}
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


