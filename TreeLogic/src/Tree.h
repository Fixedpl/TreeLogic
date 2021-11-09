#pragma once
#include "ITree.h"


template <typename T>
class Tree : public ITree<T>
{
public:

	Tree();

	INode<T>* add(const T& data);
	INode<T>* add(const T& data, const std::string& path);

private:

	RandomAddingStrategyRegularTree m_default_adding_strategy;

};


#include "Node.h"

template<typename T>
Tree<T>::Tree()
	: m_default_adding_strategy(0.3f),
	  ITree<T>(&m_default_adding_strategy)
{
}

template <typename T>
INode<T>* Tree<T>::add(const T& data) {
	return dynamic_cast<INode<T>*>(this->_add(new Node<T>(this->m_id_handler.pullId(), data)));
}

template<typename T>
INode<T>* Tree<T>::add(const T& data, const std::string& path)
{
	return dynamic_cast<INode<T>*>(this->_add(new Node<T>(data), path));
}


