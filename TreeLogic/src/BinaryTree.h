#pragma once
#include <vector>

#include "ITree.h"
#include "IAddingStrategy.h"

template <typename T>
class BinaryTree : public ITree<T>
{
private:

	RandomAddingStrategyBinaryTree<T> m_default_adding_strategy;

public:

	BinaryTree();

	INode<T>* add(const T& data);

	void remove(INode<T>* node);

	void search(const T& data, std::vector<INode<T>*>& vector_to_fill);

	void traverse(std::vector<INode<T>*>& vector_to_fill);

};

#include "BNode.h"

template<typename T>
BinaryTree<T>::BinaryTree()
	:	m_default_adding_strategy(0.4f),
		ITree<T>(&m_default_adding_strategy)
{
}

template <typename T>
INode<T>* BinaryTree<T>::add(const T& data)
{
	INode<T>* to_add = new BNode<T>(this->m_id_handler.pullId(), data);

	if (this->m_root_node == nullptr) {
		this->m_root_node = to_add;
	} else {
		this->m_current_adding_strategy->add(this->m_root_node, to_add);
	}

	return to_add;
}

template <typename T>
void BinaryTree<T>::remove(INode<T>* node)
{
	this->m_id_handler.pushId(node->getId());

	for (auto& son : node->getSons()) {
		remove(son);
	}

	if (node->m_father != nullptr) {
		dynamic_cast<BNode<T>*>(node->m_father)->removeSonPtr(node);
	} else {
		this->m_root_node = nullptr;
	}

	delete node;
}

template <typename T>
void BinaryTree<T>::search(const T& data, std::vector<INode<T>*>& vector_to_fill)
{
	if (this->m_root_node != nullptr) {
		this->m_current_traversing_strategy->search(this->m_root_node, data, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to search empty tree\n";
	}
}

template <typename T>
void BinaryTree<T>::traverse(std::vector<INode<T>*>& vector_to_fill)
{
	if (this->m_root_node != nullptr) {
		this->m_current_traversing_strategy->traverse(this->m_root_node, vector_to_fill);
	}
	else {
		std::cout << "[WARNING]Tree.h: Trying to traverse empty tree\n";
	}
}

