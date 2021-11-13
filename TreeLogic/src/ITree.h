#pragma once
#include <cmath>

#include "IDHandler.h"
#include "IAddingStrategy.h"
#include "ITraversalStrategy.h"
#include "PrettyPrintTree.h"

namespace tl
{
	class ITree
	{
	public:

		ITree();

		void remove(INode* node);

		void swapNodes(INode* first_node, INode* second_node);

		void printToConsole();

		void setAddingStrategy(IAddingStrategy* adding_strategy);

		INode* findNodeWithIDAbstract(const uint32_t& id, INode* starting_node, const int32_t& depth_limit = -1);

		uint32_t getDiameter() const;

		bool isEmpty() const;

	protected:

		INode* _add(INode* to_add);
		INode* _add(INode* to_add, const std::string& path);

		void _remove(INode* node);

		uint32_t recalculateTreeDiameter(INode* starting_node, const uint32_t& current_diameter = 0);

		void potentialDiameter(const uint32_t& path_diameter);

	protected:

		IDHandler m_id_handler;

		INode* m_root_node = nullptr;

		IAddingStrategy* m_current_adding_strategy = nullptr;

		PrettyPrintTree m_tree_printer;

		uint32_t m_tree_diameter;

	};


	template <typename T>
	class TITree : virtual public ITree
	{
	public:

		TITree(IAddingStrategy* default_adding_strategy);

		virtual ~TITree() {}

		virtual TINode<T>* add(const T& data) = 0;

		// e.g:"0 1 4" will try to find node with id 0 on first level
		// 1 on second 4 on third. if there is no node with id 4 it will
		// be created. if it exists data will be overwritten
		virtual TINode<T>* add(const T& data, const std::string& path) = 0;

		void search(const T& data, std::vector<TINode<T>*>& vector_to_fill);

		void traverse(std::vector<TINode<T>*>& vector_to_fill);

		void swapData(TINode<T>* first_node, TINode<T>* second_node);

		void setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy);

		TINode<T>* findNodeWithID(const uint32_t& id, TINode<T>* starting_node = m_root_node, const int32_t& depth_limit = -1);

		TINode<T>* getRootNode();

	protected:

		ITraversalStrategy<T>* m_current_traversing_strategy = nullptr;

		PreOrderTraversal<T> m_default_traversing_strategy;

	};


	template <typename T>
	TITree<T>::TITree(IAddingStrategy* default_adding_strategy)
		:
		m_current_traversing_strategy(&m_default_traversing_strategy)
	{
		m_current_adding_strategy = default_adding_strategy;
	}

	template<typename T>
	void TITree<T>::search(const T& data, std::vector<TINode<T>*>& vector_to_fill)
	{
		if (m_root_node != nullptr) {
			m_current_traversing_strategy->search(dynamic_cast<TINode<T>*>(m_root_node), data, vector_to_fill);
		}
		else {
			std::cout << "[WARNING]Tree.h: Trying to search empty tree\n";
		}
	}

	template<typename T>
	void TITree<T>::traverse(std::vector<TINode<T>*>& vector_to_fill)
	{
		if (m_root_node != nullptr) {
			m_current_traversing_strategy->traverse(dynamic_cast<TINode<T>*>(m_root_node), vector_to_fill);
		}
		else {
			std::cout << "[WARNING]Tree.h: Trying to traverse empty tree\n";
		}
	}

	template <typename T>
	void TITree<T>::swapData(TINode<T>* first_node, TINode<T>* second_node)
	{
		T buffor = first_node->getData();

		first_node->setData(second_node->getData());
		second_node->setData(buffor);
	}

	template <typename T>
	void TITree<T>::setTraversingStrategy(ITraversalStrategy<T>* traversing_strategy)
	{
		m_current_traversing_strategy = traversing_strategy;
	}

	// Nodes have unique ids
	template<typename T>
	TINode<T>* TITree<T>::findNodeWithID(const uint32_t& id, TINode<T>* starting_node, const int32_t& depth_limit)
	{
		if (!starting_node) {
			return nullptr;
		}
		if (starting_node->getId() == id) {
			return starting_node;
		}
		if (depth_limit) {
			for (auto& son : starting_node->getSons()) {
				TINode<T>* return_value = findNodeWithID(id, son, depth_limit - 1);
				if (return_value) {
					return return_value;
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	TINode<T>* TITree<T>::getRootNode()
	{
		return dynamic_cast<TINode<T>*>(m_root_node);
	}

	// This should be improved. Currently it only works on valid input.
	// Should throw errors when invalid input
	uint32_t first_number_to_int(const std::string& string, const uint32_t& starting_index, int32_t& output_value);
}


