#pragma once
#include <cstdlib>
#include <ctime>

typedef unsigned int uint32_t;

template <typename T>
class Node;

template <typename T>
class INode;

template <typename T>
class IAddingStrategyRegularTree
{
public:

	virtual void add(Node<T>* root, INode<T>* to_add) = 0;

};

template <typename T>
class RandomAddingStrategyRegularTree : public IAddingStrategyRegularTree<T>
{
private:

	float m_chance_of_adding_to_current_node;

public:

	RandomAddingStrategyRegularTree(float chance_of_adding_to_current_node)
		:	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node)
	{
		srand(time(0));
	}

	void add(Node<T>* root, INode<T>* to_add);
};

template <typename T>
class BalancedAddingStrategyRegularTree : public IAddingStrategyRegularTree<T>
{
private:

	uint32_t m_max_sons_per_node;

public:

	BalancedAddingStrategyRegularTree(uint32_t max_sons_per_node)
		: m_max_sons_per_node(max_sons_per_node)
	{
		srand(time(0));
	}

	void add(Node<T>* root, INode<T>* to_add);
};

#include "Node.h"

template<typename T>
void RandomAddingStrategyRegularTree<T>::add(Node<T>* root, INode<T>* to_add)
{
	float random_number = rand() / (float)(RAND_MAX);
	if (random_number <= m_chance_of_adding_to_current_node || root->sonsCount() == 0) {
		root->addSonPtr(to_add);
	}
	else {
		std::vector<INode<T>*> sons = root->getSons();
		int max = sons.size() - 1;
		int winner = rand() % (max + 1);
		sons[winner]->add(to_add);
	}
}

template<typename T>
void BalancedAddingStrategyRegularTree<T>::add(Node<T>* root, INode<T>* to_add)
{
	if (root->sonsCount() < m_max_sons_per_node) {
		root->addSonPtr(to_add);
	}
	else {
		INode<T>* smallest_subtree_node = root->getSons()[0];
		for (auto& node : root->getSons()) {
			if (node->subtreeCount() < smallest_subtree_node->subtreeCount())
				smallest_subtree_node = node;
		}
		smallest_subtree_node->add(to_add);
	}
}
