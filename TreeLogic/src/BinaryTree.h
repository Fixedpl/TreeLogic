#pragma once
#include <vector>

#include "ITree.h"
#include "IAddingStrategy.h"

namespace tl
{
	template <typename T>
	class BinaryTree : public TITree<T>
	{
	private:

		RandomAddingStrategyBinaryTree m_default_adding_strategy;

	public:

		BinaryTree();

		TINode<T>* add(const T& data);
		TINode<T>* add(const T& data, const std::string& path);

	};
}


#include "BNode.h"


namespace tl
{
	template<typename T>
	BinaryTree<T>::BinaryTree()
		:
		m_default_adding_strategy(0.4f),
		TITree<T>(&m_default_adding_strategy)
	{
	}

	template <typename T>
	TINode<T>* BinaryTree<T>::add(const T& data)
	{
		return dynamic_cast<TINode<T>*>(this->_add(new TBNode<T>(this->m_id_handler.pullId(), data)));
	}

	template<typename T>
	TINode<T>* BinaryTree<T>::add(const T& data, const std::string& path)
	{
		return dynamic_cast<TINode<T>*>(this->_add(new TBNode<T>(data), path));
	}
}



