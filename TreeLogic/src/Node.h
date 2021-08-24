#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

#include "INode.h"
#include "TreeIterator.h"



template <typename T>
class IAddingStrategy;

template <typename T>
class Node : public INode<T>
{
protected:

	std::vector<INode<T>*> m_sons;

public:

	Node(const uint32_t& id, const T& data, IAddingStrategy<T>* adding_strat);

	void add(INode<T>* to_add);

	void addSonPtr(INode<T>* node);

	void remove();

	void removeSonPtr(INode<T>* node);

	void search(const T& data, TreeIterator<INode<T>*>* treeIterator);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	std::vector<INode<T>*> getSons() { return m_sons; }

	void print(const std::string& prefix);

	void setAddingStrategy(IAddingStrategy<T>* adding_strategy);
};

#include "IAddingStrategy.h"

template <typename T>
Node<T>::Node(const uint32_t& id, const T& data, IAddingStrategy<T>* adding_strat)
{
	this->m_id = id;
	this->m_data = data;
	this->m_adding_strategy = adding_strat;
}

template<typename T>
void Node<T>::add(INode<T>* to_add)
{
	this->m_adding_strategy->add(this, to_add);
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

template<typename T>
void Node<T>::print(const std::string& prefix)
{
	std::cout << prefix << this->m_id << std::endl;
	for (auto& son : m_sons) {
		son->print("  " + prefix);
	}
}

template<typename T>
void Node<T>::setAddingStrategy(IAddingStrategy<T>* adding_strategy)
{
	this->m_adding_strategy = adding_strategy;
	for (auto& son : m_sons) {
		son->setAddingStrategy(adding_strategy);
	}
}


