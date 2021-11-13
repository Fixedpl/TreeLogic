#pragma once
#include "Tree.h"
#include "test_macros.h"



bool empty_tree_diameter()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 0;
}

// Tree diameter = 1 after normal add
bool tree_diameter_1()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	regular_tree->add("Root node");
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 1;
}

// Tree diameter = 1 after string add
bool tree_diameter_2()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	regular_tree->add("Root node", "0");
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 1;
}

// Tree diameter = 0 after deleting root
bool tree_diameter_3()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	INode* root = regular_tree->add("Root node", "0");
	regular_tree->remove(root);
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 0;
}

// Tree diameter = 2 after adding 2 sons to root
bool tree_diameter_4()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	regular_tree->add("Root node", "0");
	regular_tree->add("Root first son", "0 1");
	regular_tree->add("Root second son", "0 2");
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 2;
}

// Tree diameter = 3
bool tree_diameter_5()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	regular_tree->add("Root node", "0");
	regular_tree->add("Root first son", "0 1");
	regular_tree->add("Root second son", "0 1 2");
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 3;
}

// Tree diameter = 2
bool tree_diameter_6()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	regular_tree->add("Root node", "0");
	regular_tree->add("Root first son", "0 1");
	INode* to_remove = regular_tree->add("Root second son", "0 1 2");
	regular_tree->remove(to_remove);
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 2;
}

// Tree diameter = 2
bool tree_diameter_7()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	regular_tree->add("Root node");
	regular_tree->add("Root first son");
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 2;
}

// Tree diameter = 3
bool tree_diameter_8()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();
	IAddingStrategy* adding_strategy = new BalancedAddingStrategyRegularTree(2);
	regular_tree->setAddingStrategy(adding_strategy);
	regular_tree->add("Root node");
	regular_tree->add("Root first son");
	regular_tree->add("Root second son");
	regular_tree->add("Another son");
	uint32_t diameter = regular_tree->getDiameter();

	delete regular_tree;
	return diameter == 3;
}

void tree_diameter_tests()
{
	std::cout << "Tree diameter tests: \n\n";

	IS_TRUE(empty_tree_diameter());
	IS_TRUE(tree_diameter_1());
	IS_TRUE(tree_diameter_2());
	IS_TRUE(tree_diameter_3());
	IS_TRUE(tree_diameter_4());
	IS_TRUE(tree_diameter_5());
	IS_TRUE(tree_diameter_6());
	IS_TRUE(tree_diameter_7());
	IS_TRUE(tree_diameter_8());

	std::cout << "Tree diameter tests finished\n\n";
}
