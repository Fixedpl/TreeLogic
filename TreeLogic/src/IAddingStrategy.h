#pragma once
#include <cstdlib>
#include <ctime>
#include <cstdint>



template <typename T>
class INode;

template <typename T>
class IAddingStrategy
{
public:

	virtual void add(INode<T>* root, INode<T>* to_add) = 0;

};

template <typename T>
class RandomAddingStrategyRegularTree : public IAddingStrategy<T>
{
private:
	// [0, 1]
	float m_chance_of_adding_to_current_node;

public:

	RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node)
		:	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node)
	{
		srand(time(0));
	}

	void add(INode<T>* root, INode<T>* to_add);

	void setChanceOfAddingToCurrentNode(const float& chance_of_adding_to_current_node);
};

template <typename T>
class BalancedAddingStrategyRegularTree : public IAddingStrategy<T>
{
private:

	uint32_t m_max_sons_per_node;

public:

	BalancedAddingStrategyRegularTree(const uint32_t& max_sons_per_node)
		: m_max_sons_per_node(max_sons_per_node)
	{
	}

	void add(INode<T>* root, INode<T>* to_add);

	void setMaxSonsPerNode(const uint32_t& max_sons_per_node);
};

#include "INode.h"
#include "Node.h"

template<typename T>
void RandomAddingStrategyRegularTree<T>::add(INode<T>* root, INode<T>* to_add)
{
	float random_number = rand() / (float)(RAND_MAX);
	if (random_number <= m_chance_of_adding_to_current_node || root->sonsCount() == 0) {
		((Node<T>*)root)->addSonPtr(to_add);
	}
	else {
		std::vector<INode<T>*> sons = ((Node<T>*)root)->getSons();
		int max = sons.size() - 1;
		int winner = rand() % (max + 1);
		sons[winner]->add(to_add);
	}
}

template<typename T>
void RandomAddingStrategyRegularTree<T>::setChanceOfAddingToCurrentNode(const float& chance_of_adding_to_current_node)
{
	m_chance_of_adding_to_current_node = chance_of_adding_to_current_node;
}

template<typename T>
void BalancedAddingStrategyRegularTree<T>::add(INode<T>* root, INode<T>* to_add)
{
	if (root->sonsCount() < m_max_sons_per_node) {
		Node<T>* test = (Node<T>*)root;
		test->addSonPtr(to_add);
	}
	else {
		INode<T>* smallest_subtree_node = ((Node<T>*)root)->getSons()[0];
		for (auto& node : ((Node<T>*)root)->getSons()) {
			if (node->subtreeNodeCount() < smallest_subtree_node->subtreeNodeCount())
				smallest_subtree_node = node;
		}
		smallest_subtree_node->add(to_add);
	}
}

template<typename T>
void BalancedAddingStrategyRegularTree<T>::setMaxSonsPerNode(const uint32_t& max_sons_per_node)
{
	m_max_sons_per_node = max_sons_per_node;
}
