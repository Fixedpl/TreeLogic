#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "INode.h"



template <typename T>
class Node : public INode<T>
{
public:

	Node(const uint32_t& id, const T& data);
	Node(const T& data);

	bool addSonPtr(INode<T>* node);

	void addSonPtrRandomly(INode<T>* node);

	void removeSonPtr(INode<T>* node);

	void swapSonPtrs(INode<T>* son, INode<T>* replacement);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	std::vector<INode<T>*> getSons();

protected:

	std::vector<INode<T>*> m_sons;

	std::random_device m_random_device;
	std::mt19937 m_rng;

};

template <typename T>
Node<T>::Node(const uint32_t& id, const T& data)
:
INode<T>(id, data)
{
}

template<typename T>
Node<T>::Node(const T& data)
:
INode<T>(0, data)
{
}

template<typename T>
void Node<T>::swapSonPtrs(INode<T>* son, INode<T>* replacement)
{
	for (int i = 0; i < m_sons.size(); ++i) {
		if (son == m_sons[i]) {
			m_sons[i] = replacement;
		}
			
	}
}

template <typename T>
bool Node<T>::addSonPtr(INode<T>* node) {
	node->setFather(this);
	m_sons.push_back(node);
	return true;
}

template <typename T>
void Node<T>::addSonPtrRandomly(INode<T>* node)
{
	std::uniform_int_distribution<std::mt19937::result_type> random_int(0, m_sons.size());
	auto iterator = m_sons.begin();
	for (int i = 0; i < random_int(this->m_rng); ++i) {
		++iterator;
	}
	m_sons.insert(iterator, node);
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
