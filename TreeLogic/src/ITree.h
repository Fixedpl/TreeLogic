#pragma once
#include <cmath>

#include "IDHandler.h"
#include "IAddingStrategy.h"
#include "ITraversalStrategy.h"
#include "PrettyPrintTree.h"



template <typename T>
class ITree
{
public:

	ITree(IAddingStrategy<T>* default_adding_strategy);

	virtual ~ITree() {}

	virtual INode<T>* add(const T& data) = 0;

	// e.g:"0 1 4" will try to find node with id 0 on first level
	// 1 on second 4 on third. if there is no node with id 4 it will
	// be created. if it exists data will be overwritten
	virtual INode<T>* add(const T& data, const std::string& path) = 0;

	void remove(INode<T>* node);

	void search(const T& data, std::vector<INode<T>*>& vector_to_fill);

	void traverse(std::vector<INode<T>*>& vector_to_fill);

	void swapNodes(INode<T>* first_node, INode<T>* second_node);

	void swapData(INode<T>* first_node, INode<T>* second_node);

	void printToConsole();

	void setAddingStrategy(IAddingStrategy<T>* adding_strategy);

	void setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy);

	INode<T>* findNodeWithID(const uint32_t& id, INode<T>* starting_node = m_root_node, const int32_t& depth_limit = -1);

	INode<T>* getRootNode();

protected:

	INode<T>* _add(INode<T>* to_add);
	INode<T>* _add(INode<T>* to_add, const std::string& path);

protected:

	IDHandler m_id_handler;

	INode<T>* m_root_node = nullptr;

	IAddingStrategy<T>* m_current_adding_strategy = nullptr;

	ITraversalStrategy<T>* m_current_traversing_strategy = nullptr;

	PreOrderTraversal<T> m_default_traversing_strategy;

	PrettyPrintTree<T> m_tree_printer;

};


template <typename T>
ITree<T>::ITree(IAddingStrategy<T>* default_adding_strategy)
{
	m_current_adding_strategy = default_adding_strategy;
	m_current_traversing_strategy = &m_default_traversing_strategy;
}

template<typename T>
void ITree<T>::remove(INode<T>* node)
{
	m_id_handler.pushId(node->getId());

	for (auto& son : node->getSons()) {
		remove(son);
	}

	if (node->getFather() != nullptr) {
		node->getFather()->removeSonPtr(node);
	}
	else {
		m_root_node = nullptr;
	}

	delete node;
}

template<typename T>
void ITree<T>::search(const T& data, std::vector<INode<T>*>& vector_to_fill)
{
	if (m_root_node != nullptr) {
		m_current_traversing_strategy->search(m_root_node, data, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to search empty tree\n";
	}
}

template<typename T>
void ITree<T>::traverse(std::vector<INode<T>*>& vector_to_fill)
{
	if (m_root_node != nullptr) {
		m_current_traversing_strategy->traverse(m_root_node, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to traverse empty tree\n";
	}
}

template <typename T>
void ITree<T>::swapNodes(INode<T>* first_node, INode<T>* second_node)
{
	if (first_node == m_root_node || second_node == m_root_node) {
		std::cout << "[ERROR]Tree.h: Can't swap root node";
		return;
	}

	first_node->getFather()->swapSonPtrs(first_node, second_node);
	second_node->getFather()->swapSonPtrs(second_node, first_node);

	INode<T>* buffor = first_node->getFather();
	first_node->setFather(second_node->getFather());
	second_node->setFather(buffor);
}

template <typename T>
void ITree<T>::swapData(INode<T>* first_node, INode<T>* second_node)
{
	T buffor = first_node->getData();

	first_node->setData(second_node->getData());
	second_node->setData(buffor);
}

template <typename T>
void ITree<T>::printToConsole()
{
	if (m_root_node != nullptr) {
		m_tree_printer.print(m_root_node);
	}
	else {
		std::cout << "[WARNING]ITree.h: Trying to print empty tree\n";
	}
}

template <typename T>
void ITree<T>::setAddingStrategy(IAddingStrategy<T>* adding_strategy)
{
	m_current_adding_strategy = adding_strategy;
}

template <typename T>
void ITree<T>::setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy)
{
	m_current_traversing_strategy = traversing_strategy;
}

// Nodes have unique ids
template<typename T>
INode<T>* ITree<T>::findNodeWithID(const uint32_t& id, INode<T>* starting_node, const int32_t& depth_limit)
{
	if (!starting_node) {
		return nullptr;
	}
	if (starting_node->getId() == id) {
		return starting_node;
	}
	if (depth_limit) {
		for (auto& son : starting_node->getSons()) {
			INode<T>* return_value = findNodeWithID(id, son, depth_limit - 1);
			if (return_value) {
				return return_value;
			}
		}
	}
	return nullptr;
}

template<typename T>
INode<T>* ITree<T>::getRootNode()
{
	return m_root_node;
}

template<typename T>
INode<T>* ITree<T>::_add(INode<T>* to_add)
{
	if (m_root_node == nullptr) {
		m_root_node = to_add;
	}
	else {
		m_current_adding_strategy->add(m_root_node, to_add);
	}
	return to_add;
}

// This should be improved. Currently it only works on valid input.
// Should throw errors when invalid input
uint32_t first_number_to_int(const std::string& string, const uint32_t& starting_index, int32_t& output_value);

template<typename T>
INode<T>* ITree<T>::_add(INode<T>* to_add, const std::string& path)
{
	if (!path.size()) {
		std::cout << "[ERROR] ITree.h: Empty path passed when adding node. Abandoning insertion\n";
		return nullptr;
	}

	int32_t number_from_string = 0;
	uint32_t current_index = 0;
	current_index = first_number_to_int(path, current_index, number_from_string);
	to_add->setId(number_from_string);
	if (!m_root_node) {
		if (current_index < path.size()) {
			std::cout << "[ERROR] ITree.h: Tree has no root but more than 1 nodes included in path. Abandoning insertion\n";
			return nullptr;
		}
		m_root_node = to_add;
		return to_add;
	}
	// Overwrite root node
	if (current_index == path.size()) {
		std::cout << "[WARNING] ITree.h: Node with this id already exists. Node was overwritten\n";
		delete m_root_node;
		m_root_node = to_add;
		return to_add;
	}
	if (m_root_node->getId() != number_from_string) {
		std::cout << "[ERROR] ITree.h: Couldn't find node with id " << number_from_string << ". Abandoning insertion\n";
		return nullptr;
	}

	current_index++;
	INode<T>* current_node = m_root_node;
	INode<T>* previous_node = current_node;
	while (current_index < path.size()) {
		number_from_string = 0;

		current_index = first_number_to_int(path, current_index, number_from_string);

		previous_node = current_node;
		if ((current_node = findNodeWithID(number_from_string, current_node, 1)) == nullptr && current_index != path.size()) {
			std::cout << "[ERROR] ITree.h: Couldn't find node with id " << number_from_string << ". Abandoning insertion\n";
			return nullptr;
		}
		current_index++;
	}
	to_add->setId(number_from_string);
	if (current_node) {
		std::cout << "[WARNING] ITree.h: Node with this id already exists. Node was overwritten\n";
		previous_node->swapSonPtrs(current_node, to_add);
		delete current_node;
	} 
	else {
		if (!previous_node->addSonPtr(to_add)) {
			return nullptr;
		}
	}
	return to_add;
}
