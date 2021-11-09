#pragma once
#include <cmath>

#include "IDHandler.h"
#include "IAddingStrategy.h"
#include "ITraversalStrategy.h"
#include "PrettyPrintTree.h"

class BINode;

class BITree
{
public:

	BITree(IAddingStrategy* default_adding_strategy);

	void remove(BINode* node);

	void swapNodes(BINode* first_node, BINode* second_node);

	void printToConsole();

	void setAddingStrategy(IAddingStrategy* adding_strategy);

	BINode* findNodeWithIDAbstract(const uint32_t& id, BINode* starting_node, const int32_t& depth_limit = -1);

protected:

	BINode* _add(BINode* to_add);
	BINode* _add(BINode* to_add, const std::string& path);

protected:

	IDHandler m_id_handler;

	BINode* m_root_node = nullptr;

	IAddingStrategy* m_current_adding_strategy = nullptr;

	PrettyPrintTree m_tree_printer;

};


template <typename T>
class ITree : public BITree
{
public:

	ITree(IAddingStrategy* default_adding_strategy);

	virtual ~ITree() {}

	virtual INode<T>* add(const T& data) = 0;

	// e.g:"0 1 4" will try to find node with id 0 on first level
	// 1 on second 4 on third. if there is no node with id 4 it will
	// be created. if it exists data will be overwritten
	virtual INode<T>* add(const T& data, const std::string& path) = 0;

	void search(const T& data, std::vector<INode<T>*>& vector_to_fill);

	void traverse(std::vector<INode<T>*>& vector_to_fill);

	void swapData(INode<T>* first_node, INode<T>* second_node);

	void setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy);

	INode<T>* findNodeWithID(const uint32_t& id, INode<T>* starting_node = m_root_node, const int32_t& depth_limit = -1);

	INode<T>* getRootNode();

protected:

	ITraversalStrategy<T>* m_current_traversing_strategy = nullptr;

	PreOrderTraversal<T> m_default_traversing_strategy;

};


template <typename T>
ITree<T>::ITree(IAddingStrategy* default_adding_strategy)
:
BITree(default_adding_strategy),
m_current_traversing_strategy(&m_default_traversing_strategy)
{
}

template<typename T>
void ITree<T>::search(const T& data, std::vector<INode<T>*>& vector_to_fill)
{
	if (m_root_node != nullptr) {
		m_current_traversing_strategy->search(dynamic_cast<INode<T>*>(m_root_node), data, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to search empty tree\n";
	}
}

template<typename T>
void ITree<T>::traverse(std::vector<INode<T>*>& vector_to_fill)
{
	if (m_root_node != nullptr) {
		m_current_traversing_strategy->traverse(dynamic_cast<INode<T>*>(m_root_node), vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to traverse empty tree\n";
	}
}

template <typename T>
void ITree<T>::swapData(INode<T>* first_node, INode<T>* second_node)
{
	T buffor = first_node->getData();

	first_node->setData(second_node->getData());
	second_node->setData(buffor);
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
	return dynamic_cast<INode<T>*>(m_root_node);
}

// This should be improved. Currently it only works on valid input.
// Should throw errors when invalid input
uint32_t first_number_to_int(const std::string& string, const uint32_t& starting_index, int32_t& output_value);
