﻿#pragma once
#include <iostream>

#include "ITree.h"

template <typename T>
class INode;

template <typename T>
class Tree : public ITree<T>
{
private:

	RandomAddingStrategyRegularTree<T> m_default_adding_strategy;

public:

	Tree();

	INode<T>* add(const T& data);

	void remove(INode<T>* node);

	void search(const T& data, std::vector<INode<T>*>& vector_to_fill);

	void traverse(std::vector<INode<T>*>& vector_to_fill);

};

#include "INode.h"
#include "Node.h"

template<typename T>
Tree<T>::Tree()
	: m_default_adding_strategy(0.3f),
	  ITree<T>(&m_default_adding_strategy)
{
}

template <typename T>
INode<T>* Tree<T>::add(const T& data) {

	INode<T>* to_add = new Node<T>(this->m_id_handler.pullId(), data);

	if (this->m_root_node == nullptr) {
		this->m_root_node = to_add;
	} else {
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
	} else {
		std::cout << "[WARNING]Tree.h: Trying to search empty tree\n";
	}
}

template<typename T>
void Tree<T>::traverse(std::vector<INode<T>*>& vector_to_fill)
{
	if (this->m_root_node != nullptr) {
		this->m_current_traversing_strategy->traverse(this->m_root_node, vector_to_fill);
	} else {
		std::cout << "[WARNING]Tree.h: Trying to traverse empty tree\n";
	}
}
