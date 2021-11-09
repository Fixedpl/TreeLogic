#pragma once
#include "Tree.h"
#include "BinaryTree.h"
#define IS_TRUE(x) { if (!(x)) {std::cout << __FUNCTION__ << " failed on line " << __LINE__ << "\n";}else{ std::cout << "Passed\n";} }
#define TEST_WARNING { std::cout << "\t Expected warning: "; }
#define TEST_ERROR { std::cout << "\t Expected error: "; }

// Try to add child of root but no root
bool regular_tree_path_adding_0()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	TEST_ERROR;
	TINode<std::string>* node = regular_tree->add("First node", "0 1");

	delete regular_tree;
	return node == nullptr;
}

// Add as root
bool regular_tree_path_adding_1()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");

	uint32_t id = regular_tree->getRootNode()->getId();

	delete regular_tree;
	return id == 0;
}

// Add as root when root already exists with different id
bool regular_tree_path_adding_2()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");

	TEST_WARNING;
	regular_tree->add("Overwrite node", "1");

	uint32_t id = regular_tree->getRootNode()->getId();

	delete regular_tree;
	return id == 1;
}

// Add as root when root already exists with the same id
bool regular_tree_path_adding_3()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	TEST_WARNING;
	regular_tree->add("Overwrite node", "0");

	std::string data = regular_tree->getRootNode()->getData();

	delete regular_tree;
	return data == "Overwrite node";
}

// Add root and then child
bool regular_tree_path_adding_4()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	regular_tree->add("Second node", "0 1");

	TINode<std::string>* it = regular_tree->getRootNode();
	it = it->getSons()[0];

	uint32_t id = it->getId();

	delete regular_tree;
	return id == 1;
}

// Add root and then wrong path
bool regular_tree_path_adding_5()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	TEST_ERROR;
	TINode<std::string>* node = regular_tree->add("Second node", "1 2");

	delete regular_tree;
	return node == nullptr;
}

// Add root and then wrong path
bool regular_tree_path_adding_6()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	TEST_ERROR;
	TINode<std::string>* node = regular_tree->add("Second node", "0 1 2");

	delete regular_tree;
	return node == nullptr;
}

// Add root and then overwrite with the same id
bool regular_tree_path_adding_7()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	regular_tree->add("Second node", "0 1");
	TEST_WARNING;
	regular_tree->add("Overwrite node", "0 1");

	TINode<std::string>* node = regular_tree->getRootNode();
	
	std::string value = node->getSons()[0]->getData();

	delete regular_tree;
	return value == "Overwrite node";
}

// Add root and 2 children
bool regular_tree_path_adding_8()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	regular_tree->add("Second node", "0 1");
	regular_tree->add("Third node", "0 2");

	TINode<std::string>* node = regular_tree->getRootNode();

	std::string value = node->getSons()[1]->getData();

	delete regular_tree;
	return value == "Third node";
}

// Add root and 3 children
bool regular_tree_path_adding_9()
{
	TITree<std::string>* regular_tree = new Tree<std::string>();

	regular_tree->add("First node", "0");
	regular_tree->add("Second node", "0 1");
	regular_tree->add("Third node", "0 2");
	regular_tree->add("Fourth node", "0 3");

	TINode<std::string>* node = regular_tree->getRootNode();

	std::string value = node->getSons()[2]->getData();

	delete regular_tree;
	return value == "Fourth node";
}

// Try to add more than 2 nodes to 1 node
bool binary_tree_path_adding_0()
{
	TITree<std::string>* binary_tree = new BinaryTree<std::string>();

	binary_tree->add("First node", "0");
	binary_tree->add("Second node", "0 1");
	binary_tree->add("Third node", "0 2");
	TEST_ERROR;
	TINode<std::string>* node = binary_tree->add("Fourth node", "0 3");


	delete binary_tree;
	return node == nullptr;
}


void regular_tree_path_adding()
{
	bool test = false;
	std::cout << "Regular tree path adding tests: \n";

	
	IS_TRUE(regular_tree_path_adding_0());
	IS_TRUE(regular_tree_path_adding_1());
	IS_TRUE(regular_tree_path_adding_2());
	IS_TRUE(regular_tree_path_adding_3());
	IS_TRUE(regular_tree_path_adding_5());
	IS_TRUE(regular_tree_path_adding_6());
	IS_TRUE(regular_tree_path_adding_7());
	IS_TRUE(regular_tree_path_adding_8());
	IS_TRUE(regular_tree_path_adding_9());

	IS_TRUE(binary_tree_path_adding_0());
}


