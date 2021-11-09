#pragma once
#include <vector>

#include "ITree.h"
#include "IAddingStrategy.h"

template <typename T>
class BinaryTree : public ITree<T>
{
private:

	RandomAddingStrategyBinaryTree m_default_adding_strategy;

public:

	BinaryTree();

	INode<T>* add(const T& data);
	INode<T>* add(const T& data, const std::string& path);

};

#include "BNode.h"

template<typename T>
BinaryTree<T>::BinaryTree()
:	
m_default_adding_strategy(0.4f),
ITree<T>(&m_default_adding_strategy)
{
}

template <typename T>
INode<T>* BinaryTree<T>::add(const T& data)
{
	return dynamic_cast<INode<T>*>(this->_add(new BBNode<T>(this->m_id_handler.pullId(), data)));
}

template<typename T>
INode<T>* BinaryTree<T>::add(const T& data, const std::string& path)
{
	return dynamic_cast<INode<T>*>(this->_add(new BBNode<T>(data), path));
}


