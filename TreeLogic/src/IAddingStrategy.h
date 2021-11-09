#pragma once
#include <cstdlib>
#include <random>
#include <ctime>
#include <cstdint>
#include <vector>



class BINode;

class BITree;

enum class AdditionalCondition {
	BTree2Nodes
};


class IAddingStrategy
{
public:

	virtual void add(BINode* root, BINode* to_add) = 0;

};

class RandomAddingStrategyRegularTree : public IAddingStrategy
{
private:
	// [0, 1]
	float m_chance_of_adding_to_current_node;

	std::random_device m_random_device;
	std::mt19937 m_rng;

	std::vector<AdditionalCondition> m_additional_conditions;

public:

	void add(BINode* root, BINode* to_add);

private:

	bool additionalCheck(const AdditionalCondition& additional_condition, BINode* node);

protected:

	// FOR INHERITING CLASSES
	RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node, const AdditionalCondition& additional_condition);


public:

	RandomAddingStrategyRegularTree(const float& chance_of_adding_to_current_node = 0.3f);

	void setChanceOfAddingToCurrentNode(const float& chance_of_adding_to_current_node);

};

class BalancedAddingStrategyRegularTree : public IAddingStrategy
{
private:

	uint32_t m_max_sons_per_node;

public:

	void add(BINode* root, BINode* to_add);

public:

	BalancedAddingStrategyRegularTree(const uint32_t& max_sons_per_node = 3);

	void setMaxSonsPerNode(const uint32_t& max_sons_per_node);
};


class RandomAddingStrategyBinaryTree : public RandomAddingStrategyRegularTree
{
private:

	AdditionalCondition m_limit_to_2_nodes;

public:

	RandomAddingStrategyBinaryTree(const float& chance_of_adding_to_current_node = 0.4f);

};

class BalancedAddingStrategyBinaryTree : public BalancedAddingStrategyRegularTree
{
public:

	BalancedAddingStrategyBinaryTree(const uint32_t& max_sons_per_node = 2);
};


