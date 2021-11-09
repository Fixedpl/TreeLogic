#pragma once
#include "ITree.h"


template <typename T>
class Tree : public TITree<T>
{
public:

	Tree();

	TINode<T>* add(const T& data);
	TINode<T>* add(const T& data, const std::string& path);

private:

	RandomAddingStrategyRegularTree m_default_adding_strategy;

};


#include "Node.h"

template<typename T>
Tree<T>::Tree()
: 
m_default_adding_strategy(0.3f),
TITree<T>(&m_default_adding_strategy)
{
}

template <typename T>
TINode<T>* Tree<T>::add(const T& data) {
	return dynamic_cast<TINode<T>*>(this->_add(new TNode<T>(this->m_id_handler.pullId(), data)));
}

template<typename T>
TINode<T>* Tree<T>::add(const T& data, const std::string& path)
{
	return dynamic_cast<TINode<T>*>(this->_add(new TNode<T>(data), path));
}


