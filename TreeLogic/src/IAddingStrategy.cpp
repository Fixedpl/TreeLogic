#include "IAddingStrategy.h"
#include "Node.h"

bool RandomAddingStrategyRegularTree::additionalCheck(const AdditionalCondition& additional_condition, BINode* node)
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

RandomAddingStrategyRegularTree::RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node, const AdditionalCondition& additional_condition)
	:
	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node),
	m_rng(m_random_device())
{
	srand(time(0));
	m_additional_conditions.push_back(additional_condition);
}

RandomAddingStrategyRegularTree::RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node)
	:
	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node)
{
	srand(time(0));
}

void RandomAddingStrategyRegularTree::add(BINode* root, BINode* to_add)
{
	std::uniform_real_distribution<float> random_float(0.0f, 1.0f);
	// Adding as son of root
	if ((random_float(m_rng) <= m_chance_of_adding_to_current_node && additionalCheck(AdditionalCondition::BTree2Nodes, root))
		|| root->sonsCount() == 0) {
		root->addSonPtrRandomly(to_add);
	}
	else {
		// Adding deeper in the tree
		std::vector<BINode*> sons = root->getSonsAbstract();
		std::uniform_int_distribution<std::mt19937::result_type> random_int(0, sons.size() - 1);
		add(sons[random_int(m_rng)], to_add);
	}
}

void RandomAddingStrategyRegularTree::setChanceOfAddingToCurrentNode(const float& chance_of_adding_to_current_node)
{
	m_chance_of_adding_to_current_node = chance_of_adding_to_current_node;
}

BalancedAddingStrategyRegularTree::BalancedAddingStrategyRegularTree(const uint32_t& max_sons_per_node)
	:
	m_max_sons_per_node(max_sons_per_node)
{
}

void BalancedAddingStrategyRegularTree::add(BINode* root, BINode* to_add)
{
	// Adding as son of root
	if (root->sonsCount() < m_max_sons_per_node) {
		root->addSonPtr(to_add);
	}
	else {
		// Adding deeper in the tree
		BINode* smallest_subtree_node = root->getSonsAbstract()[0];
		for (auto& node : root->getSonsAbstract()) {
			if (node->subtreeNodeCount() < smallest_subtree_node->subtreeNodeCount())
				smallest_subtree_node = node;
		}
		add(smallest_subtree_node, to_add);
	}
}

void BalancedAddingStrategyRegularTree::setMaxSonsPerNode(const uint32_t& max_sons_per_node)
{
	m_max_sons_per_node = max_sons_per_node;
}

RandomAddingStrategyBinaryTree::RandomAddingStrategyBinaryTree(const float& chance_of_adding_to_current_node)
	:
	m_limit_to_2_nodes(AdditionalCondition::BTree2Nodes),
	RandomAddingStrategyRegularTree(chance_of_adding_to_current_node, m_limit_to_2_nodes)
{
}

BalancedAddingStrategyBinaryTree::BalancedAddingStrategyBinaryTree(const uint32_t& max_sons_per_node)
	:
	BalancedAddingStrategyRegularTree(max_sons_per_node)
{
}

