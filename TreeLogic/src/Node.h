#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "INode.h"


class BNode : virtual public BINode
{
public:

	BNode();

	bool addSonPtr(BINode* node);

	void addSonPtrRandomly(BINode* node);

	void removeSonPtr(BINode* node);

	void swapSonPtrs(BINode* son, BINode* replacement);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	std::vector<BINode*> getSonsAbstract();

protected:

	std::vector<BINode*> m_sons;

};

template <typename T>
class Node : public BNode, public INode<T>
{
public:

	Node(const uint32_t& id, const T& data);
	Node(const T& data);

	std::vector<INode<T>*> getSons();

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
std::vector<INode<T>*> Node<T>::getSons()
{
	std::vector<INode<T>*> final_vector;
	for (auto& son : m_sons) {
		final_vector.push_back(dynamic_cast<INode<T>*>(son));
	}
	return final_vector;
}

