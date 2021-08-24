#pragma once
#include <iostream>

#include "ITree.h"
#include "Node.h"
#include "TreeIterator.h"

template <typename T>
class Tree : public ITree<T>
{

public:

	INode<T>* add(const T& data);

	void remove(INode<T>* node);

	Iterator<INode<T>*>* search(const T& data);

	void swapNodes(INode<T>* first_node, INode<T>* second_node);

	void swapData(INode<T>* first_node, INode<T>* second_node);
};


template <typename T>
INode<T>* Tree<T>::add(const T& data) {

	INode<T>* newNode = new Node<T>(data);

	if (this->m_root_node == nullptr) {
		this->m_root_node = newNode;
	}
	else {
		// TODO: Use dynamic_cast
		Node<T>* root_node_downcast = (Node<T>*) this->m_root_node;

		root_node_downcast->addSonPtr(newNode);
	}

	return newNode;
}

template <typename T>
void Tree<T>::remove(INode<T>* node) {
	node->remove();

	if (node->m_father != nullptr) {
		Node<T>* node_father = (Node<T>*) node->m_father;

		node_father->removeSonPtr(node);
	} else {
		this->m_root_node = nullptr;
	}
		
	delete node;
}

template<typename T>
Iterator<INode<T>*>* Tree<T>::search(const T& data) {
	TreeIterator<INode<T>*>* treeIterator = new TreeIterator<INode<T>*>();

	if (this->m_root_node->getData() == data)
		treeIterator->add(this->m_root_node);

	this->m_root_node->search(data, treeIterator);

	return treeIterator;
}

template<typename T>
void Tree<T>::swapNodes(INode<T>* first_node, INode<T>* second_node)
{
	if (first_node == this->m_root_node || second_node == this->m_root_node) {
		std::cout << "[Tree.h]ERROR: Can't swap root node";
		return;
	}

	// TODO: Use dynamic_cast
	Node<T>* first_node_father = (Node<T>*) first_node->m_father;
	Node<T>* second_node_father = (Node<T>*) second_node->m_father;

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

