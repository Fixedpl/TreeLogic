#pragma once
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "INode.h"

template <typename T>
class BNode : public INode<T>
{
public:

	BNode(const uint32_t& id, const T& data);
	BNode(const T& data);

	bool addSonPtr(INode<T>* node);

	void addSonPtrRandomly(INode<T>* node);

	void removeSonPtr(INode<T>* node);

	void swapSonPtrs(INode<T>* son, INode<T>* replacement);

	std::vector<INode<T>*> getSons();

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	INode<T>* getLeftSon();
	INode<T>* getRightSon();

	void setLeftSon(INode<T>* node);
	void setRightSon(INode<T>* node);

protected:

	INode<T>* m_left_son = nullptr;
	INode<T>* m_right_son = nullptr;

};

template <typename T>
BNode<T>::BNode(const uint32_t& id, const T& data)
:
INode<T>(id, data)
{
}

template<typename T>
BNode<T>::BNode(const T& data)
:
INode<T>(0, data)
{
}

template <typename T>
bool BNode<T>::addSonPtr(INode<T>* node)
{
	if (m_left_son && m_right_son) {
		std::cout << "[ERROR] BNode.h: Couldn't add son because BNode already has 2 sons\n";
		return false;
	}
	if (!m_left_son) {
		m_left_son = node;
	}
	else {
		m_right_son = node;
	}
	return true;
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

template<typename T>
INode<T>* BNode<T>::getLeftSon()
{
	return m_left_son;
}

template<typename T>
inline INode<T>* BNode<T>::getRightSon()
{
	return m_right_son;
}

template<typename T>
void BNode<T>::setLeftSon(INode<T>* node)
{
	if (m_left_son) {
		std::cout << "[WARNING] BNode.h: Binary node already has left. Node was overwritten\n";
	}
	m_left_son = node;
}

template<typename T>
void BNode<T>::setRightSon(INode<T>* node)
{
	if (m_left_son) {
		std::cout << "[WARNING] BNode.h: Binary node already has right son. Node was overwritten\n";
	}
	m_right_son = node;
}

