#pragma once
#include <iostream>

#include "ITree.h"

#include "IAddingStrategy.h"
#include "ITraversalStrategy.h"
#include "PrettyPrintTree.h"

template <typename T>
class INode;

template <typename T>
class Tree : public ITree<T>
{
private:

	RandomAddingStrategyRegularTree<T> m_default_adding_strategy;

	PreOrderTraversal<T> m_default_traversing_strategy;

	PrettyPrintTree<T> m_tree_printer;

public:

	Tree() 
		: m_default_adding_strategy(0.25f)
	{
		this->m_current_adding_strategy = &m_default_adding_strategy;
		this->m_current_traversing_strategy = &m_default_traversing_strategy;
	}

	INode<T>* add(const T& data);

	void remove(INode<T>* node);

	void search(const T& data, std::vector<INode<T>*>& vector_to_fill);

	void traverse(std::vector<INode<T>*>& vector_to_fill);

	void swapNodes(INode<T>* first_node, INode<T>* second_node);

	void swapData(INode<T>* first_node, INode<T>* second_node);

	void printToConsole();

};

#include "INode.h"
#include "Node.h"

template <typename T>
INode<T>* Tree<T>::add(const T& data) {

	INode<T>* to_add = new Node<T>(this->m_id_handler.pullId(), data);

	if (this->m_root_node == nullptr) {
		this->m_root_node = to_add;
	}
	else {
		this->m_current_adding_strategy->add(this->m_root_node, to_add);
	}

	return to_add;
}

template <typename T>
void Tree<T>::remove(INode<T>* node) {

	this->m_id_handler.pushId(node->getId());

	for (auto& son : node->getSons()) {
		remove(son);
	}

	if (node->m_father != nullptr) {
		dynamic_cast<Node<T>*>(node->m_father)->removeSonPtr(node);
	} else {
		this->m_root_node = nullptr;
	}
		
	delete node;
}

template<typename T>
void Tree<T>::search(const T& data, std::vector<INode<T>*>& vector_to_fill) {
	if (this->m_root_node != nullptr) {
		this->m_current_traversing_strategy->search(this->m_root_node, data, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to search empty tree\n";
	}
}

template<typename T>
void Tree<T>::traverse(std::vector<INode<T>*>& vector_to_fill)
{
	if (this->m_root_node != nullptr) {
		this->m_current_traversing_strategy->traverse(this->m_root_node, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to traverse empty tree\n";
	}
}

template<typename T>
void Tree<T>::swapNodes(INode<T>* first_node, INode<T>* second_node)
{
	if (first_node == this->m_root_node || second_node == this->m_root_node) {
		std::cout << "[ERROR]Tree.h: Can't swap root node";
		return;
	}

	Node<T>* first_node_father = dynamic_cast<Node<T>*>(first_node->m_father);
	Node<T>* second_node_father = dynamic_cast<Node<T>*>(second_node->m_father);

	first_node_father->addSonPtr(second_node);
	second_node_father->addSonPtr(first_node);

	first_node_father->removeSonPtr(first_node);
	second_node_father->removeSonPtr(second_node);

}

template<typename T>
void Tree<T>::swapData(INode<T>* first_node, INode<T>* second_node)
{
	T buffor = first_node->getData();

	first_node->setData(second_node->getData());
	second_node->setData(buffor);
}

template<typename T>
void Tree<T>::printToConsole()
{
	if (this->m_root_node != nullptr)
		m_tree_printer.print(this->m_root_node);
	else
		std::cout << "[WARNING]Tree.h: Trying to print empty tree\n";
}

