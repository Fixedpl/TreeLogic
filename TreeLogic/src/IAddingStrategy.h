#pragma once
#include <cstdlib>
#include <random>
#include <ctime>
#include <cstdint>
#include <vector>



template <typename T>
class INode;

enum class AdditionalCondition {
	BTree2Nodes
};

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

	std::random_device m_random_device;
	std::mt19937 m_rng;

	std::vector<AdditionalCondition> m_additional_conditions;

private:

	bool additionalCheck(const AdditionalCondition& additional_condition, INode<T>* node);

protected:

	RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node, const AdditionalCondition& additional_condition)
		:	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node),
			m_rng(m_random_device())
	{
		srand(time(0));
		m_additional_conditions.push_back(additional_condition);
	}

public:

	RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node = 0.3f)
		:	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node)
	{
		srand(time(0));
	}

	void add(INode<T>* root, INode<T>* to_add);

	void setChanceOfAddingToCurrentNode(const float& chance_of_adding_to_current_node)
		{ m_chance_of_adding_to_current_node = chance_of_adding_to_current_node; }
};

template <typename T>
class BalancedAddingStrategyRegularTree : public IAddingStrategy<T>
{
private:

	uint32_t m_max_sons_per_node;

public:

	BalancedAddingStrategyRegularTree(const uint32_t& max_sons_per_node = 3)
		: m_max_sons_per_node(max_sons_per_node)
	{
	}

	void add(INode<T>* root, INode<T>* to_add);

	void setMaxSonsPerNode(const uint32_t& max_sons_per_node) { m_max_sons_per_node = max_sons_per_node; }
};

template <typename T>
class RandomAddingStrategyBinaryTree : public RandomAddingStrategyRegularTree<T>
{
private:

	AdditionalCondition m_limit_to_2_nodes;

public:

	RandomAddingStrategyBinaryTree(const float& chance_of_adding_to_current_node = 0.4f)
		:	m_limit_to_2_nodes(AdditionalCondition::BTree2Nodes),
			RandomAddingStrategyRegularTree<T>(chance_of_adding_to_current_node, m_limit_to_2_nodes)
	{
	}

};

template <typename T>
class BalancedAddingStrategyBinaryTree : public BalancedAddingStrategyRegularTree<T>
{
public:

	BalancedAddingStrategyBinaryTree(const uint32_t& max_sons_per_node = 2)
		: BalancedAddingStrategyRegularTree<T>(max_sons_per_node)
	{
	}
};

#include "INode.h"
#include "Node.h"

template <typename T>
bool RandomAddingStrategyRegularTree<T>::additionalCheck(const AdditionalCondition& additional_condition, INode<T>* node)
{
	if (std::find(m_additional_conditions.begin(), m_additional_conditions.end(), additional_condition) != m_additional_conditions.end()) {
		switch (additional_condition) {
		case AdditionalCondition::BTree2Nodes: {
			if (node->sonsCount() == 2)
				return false;
		}
		}
	}
	return true;
}

template <typename T>
void RandomAddingStrategyRegularTree<T>::add(INode<T>* root, INode<T>* to_add)
{
	std::uniform_real_distribution<float> random_float(0.0f, 1.0f);
	// Adding as son of root
	if ((	random_float(m_rng) <= m_chance_of_adding_to_current_node && additionalCheck(AdditionalCondition::BTree2Nodes, root)) 
		||	root->sonsCount() == 0) {
		root->addSonPtrRandomly(to_add);
	}
	else {
		// Adding deeper in the tree
		std::vector<INode<T>*> sons = root->getSons();
		std::uniform_int_distribution<std::mt19937::result_type> random_int(0, sons.size() - 1);
		add(sons[random_int(m_rng)], to_add);
	}
}

template <typename T>
void BalancedAddingStrategyRegularTree<T>::add(INode<T>* root, INode<T>* to_add)
{
	// Adding as son of root
	if (root->sonsCount() < m_max_sons_per_node) {
		root->addSonPtr(to_add);
	}
	else {
		// Adding deeper in the tree
		INode<T>* smallest_subtree_node = root->getSons()[0];
		for (auto& node : root->getSons()) {
			if (node->subtreeNodeCount() < smallest_subtree_node->subtreeNodeCount())
				smallest_subtree_node = node;
		}
		add(smallest_subtree_node, to_add);
	}
}
