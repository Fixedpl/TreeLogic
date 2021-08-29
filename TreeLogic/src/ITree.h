#pragma once
#include "Iterator.h"
#include "IDHandler.h"

template <typename T>
class IAddingStrategy;

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

public:

	virtual ~ITree() {}

	virtual INode<T>* add(const T& data) = 0;

	virtual void remove(INode<T>* node) = 0;

	virtual Iterator<INode<T>*>* search(const T& data) = 0;

	virtual Iterator<INode<T>*>* traverse() = 0;

	virtual void swapNodes(INode<T>* first_node, INode<T>* second_node) = 0;

	virtual void swapData(INode<T>* first_node, INode<T>* second_node) = 0;

	virtual void printToConsole() = 0;

	void setAddingStrategy(IAddingStrategy<T>* adding_strategy);

	void setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy);
};

#include "IAddingStrategy.h"
#include "ITraversalStrategy.h"

template<typename T>
void ITree<T>::setAddingStrategy(IAddingStrategy<T>* adding_strategy)
{
	m_current_adding_strategy = adding_strategy;
}

template<typename T>
void ITree<T>::setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy)
{
	m_current_traversing_strategy = traversing_strategy;
}
