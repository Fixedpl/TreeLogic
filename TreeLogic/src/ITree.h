#pragma once
#include "IDHandler.h"
#include "IAddingStrategy.h"
#include "ITraversalStrategy.h"
#include "PrettyPrintTree.h"



template <typename T>
class ITraversalStrategy;

template <typename T>
class INode;

template <typename T>
class ITree
{
protected:

	INode<T>* m_root_node = nullptr;

	IDHandler m_id_handler;

	IAddingStrategy<T>* m_current_adding_strategy = nullptr;

	ITraversalStrategy<T>* m_current_traversing_strategy = nullptr;

	PreOrderTraversal<T> m_default_traversing_strategy;

	PrettyPrintTree<T> m_tree_printer;

public:

	ITree(IAddingStrategy<T>* default_adding_strategy);

	virtual ~ITree() {}

	virtual INode<T>* add(const T& data) = 0;

	virtual void remove(INode<T>* node) = 0;

	virtual void search(const T& data, std::vector<INode<T>*>& vector_to_fill) = 0;

	virtual void traverse(std::vector<INode<T>*>& vector_to_fill) = 0;

	void swapNodes(INode<T>* first_node, INode<T>* second_node);

	void swapData(INode<T>* first_node, INode<T>* second_node);

	void printToConsole();

	void setAddingStrategy(IAddingStrategy<T>* adding_strategy);

	void setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy);
};


template <typename T>
ITree<T>::ITree(IAddingStrategy<T>* default_adding_strategy)
{
	m_current_adding_strategy = default_adding_strategy;
	m_current_traversing_strategy = &m_default_traversing_strategy;
}

template <typename T>
void ITree<T>::swapNodes(INode<T>* first_node, INode<T>* second_node)
{
	if (first_node == this->m_root_node || second_node == this->m_root_node) {
		std::cout << "[ERROR]Tree.h: Can't swap root node";
		return;
	}

	first_node->m_father->swapSonPtrs(first_node, second_node);
	second_node->m_father->swapSonPtrs(second_node, first_node);

	INode<T>* buffor = first_node->m_father;
	first_node->m_father = second_node->m_father;
	second_node->m_father = buffor;
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
	if (this->m_root_node != nullptr)
		this->m_tree_printer.print(this->m_root_node);
	else
		std::cout << "[WARNING]ITree.h: Trying to print empty tree\n";
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
