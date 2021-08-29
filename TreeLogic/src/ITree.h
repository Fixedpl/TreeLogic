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

	IAddingStrategy<T>* m_current_adding_strategy;

	ITraversalStrategy<T>* m_current_traversing_strategy;

public:

	virtual ~ITree() {}

	virtual INode<T>* add(const T& data) = 0;

	virtual void remove(INode<T>* node) = 0;

	virtual Iterator<INode<T>*> search(const T& data) = 0;

	virtual void swapNodes(INode<T>* first_node, INode<T>* second_node) = 0;

	virtual void swapData(INode<T>* first_node, INode<T>* second_node) = 0;

	virtual void printToConsole() = 0;

	virtual void setAddingStrategy(IAddingStrategy<T>* adding_strategy) = 0;
};

