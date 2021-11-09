#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "INode.h"


class Node : virtual public INode
{
public:

	Node();

	bool addSonPtr(INode* node);

	void addSonPtrRandomly(INode* node);

	void removeSonPtr(INode* node);

	void swapSonPtrs(INode* son, INode* replacement);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	std::vector<INode*> getSonsAbstract();

protected:

	std::vector<INode*> m_sons;

};

template <typename T>
class TNode : public Node, public TINode<T>
{
public:

	TNode(const uint32_t& id, const T& data);
	TNode(const T& data);

	std::vector<TINode<T>*> getSons();

};

template <typename T>
TNode<T>::TNode(const uint32_t& id, const T& data)
:
TINode<T>(id, data)
{
}

template<typename T>
TNode<T>::TNode(const T& data)
:
TINode<T>(0, data)
{
}

template<typename T>
std::vector<TINode<T>*> TNode<T>::getSons()
{
	std::vector<TINode<T>*> final_vector;
	for (auto& son : m_sons) {
		final_vector.push_back(dynamic_cast<TINode<T>*>(son));
	}
	return final_vector;
}

