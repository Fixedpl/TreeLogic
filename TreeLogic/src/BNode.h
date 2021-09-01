#pragma once
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "INode.h"

template <typename T>
class BNode : public INode<T>
{
protected:

	INode<T>* m_left_son = nullptr;
	INode<T>* m_right_son = nullptr;

public:

	BNode(const uint32_t& id, const T& data);

	void addSonPtr(INode<T>* node);

	void addSonPtrRandomly(INode<T>* node);

	void removeSonPtr(INode<T>* node);

	void swapSonPtrs(INode<T>* son, INode<T>* replacement);

	std::vector<INode<T>*> getSons();

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();



};

template <typename T>
BNode<T>::BNode(const uint32_t& id, const T& data)
	:	INode<T>(id, data)
{
}

template <typename T>
void BNode<T>::addSonPtr(INode<T>* node)
{
	if (!m_left_son)
		m_left_son = node;
	else
		m_right_son = node;
}

template <typename T>
void BNode<T>::addSonPtrRandomly(INode<T>* node)
{
	std::uniform_real_distribution<float> random_float(0.0f, 1.0f);
	if (!m_left_son && !m_right_son) {
		if (random_float(this->m_rng) <= 0.5f)
			m_left_son = node;
		else
			m_right_son = node;
	} else {
		addSonPtr(node);
	}
}

template <typename T>
void BNode<T>::removeSonPtr(INode<T>* node)
{
	if (m_left_son == node)
		m_left_son = nullptr;
	else
		m_right_son = nullptr;
}

template <typename T>
void BNode<T>::swapSonPtrs(INode<T>* son, INode<T>* replacement)
{
	if (m_left_son == son)
		m_left_son = replacement;
	else
		m_right_son = replacement;
}

template <typename T>
std::vector<INode<T>*> BNode<T>::getSons()
{
	std::vector<INode<T>*> sons;
	if (m_left_son != nullptr)
		sons.push_back(m_left_son);
	if (m_right_son != nullptr)
		sons.push_back(m_right_son);

	return sons;
}

template <typename T>
uint32_t BNode<T>::sonsCount()
{
	if (m_left_son && m_right_son)
		return 2;
	else if (!m_left_son && !m_right_son)
		return 0;
	return 1;
}

template <typename T>
uint32_t BNode<T>::subtreeNodeCount()
{
	uint32_t count = 1;
	if(m_left_son)
		count += m_left_son->subtreeNodeCount();
	if(m_right_son)
		count += m_right_son->subtreeNodeCount();
	return count;
}

