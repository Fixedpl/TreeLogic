#pragma once
#include "INode.h"
#include "Iterator.h"
#include "IDHandler.h"

template <typename T>
class ITree
{
protected:

	INode<T>* m_root_node = nullptr;

	IDHandler m_id_handler;

public:

	virtual ~ITree() {}

	virtual INode<T>* add(const T& data) = 0;

	virtual void remove(INode<T>* node) = 0;

	virtual Iterator<INode<T>*>* search(const T& data) = 0;

	virtual void swapNodes(INode<T>* first_node, INode<T>* second_node) = 0;

	virtual void swapData(INode<T>* first_node, INode<T>* second_node) = 0;

	virtual void printToConsole() = 0;
};

