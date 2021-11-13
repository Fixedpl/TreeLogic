#pragma once
#include <cassert>
#include <queue>


template <typename T>
class TINode;


//		NO_CONDITION - All nodes on the way are added to vector
//		SAME_DATA	 - Only nodes with the same data are added to vector
enum class AddCondition { NO_CONDITION, SAME_DATA };

template <typename T>
class ITraversalStrategy
{
public:

	ITraversalStrategy(const AddCondition& add_condition);

	virtual void search(TINode<T>* root, const T& data, std::vector<TINode<T>*>& vector_to_fill) = 0;

	void traverse(TINode<T>* root, std::vector<TINode<T>*>& vector_to_fill);

protected:

	void add(TINode<T>* root, 
			 const T& data, 
			 std::vector<TINode<T>*>& vector_to_fill);

public:

	AddCondition m_add_condition;

};

template <typename T>
class PreOrderTraversal : public ITraversalStrategy<T>
{
public:

	PreOrderTraversal(const AddCondition& add_condition = AddCondition::SAME_DATA);

	void search(TINode<T>* root, const T& data, std::vector<TINode<T>*>& vector_to_fill);

};

template <typename T>
class InOrderTraversal : public ITraversalStrategy<T>
{
public:

	InOrderTraversal(const AddCondition& add_condition = AddCondition::SAME_DATA);

	void search(TINode<T>* root, const T& data, std::vector<TINode<T>*>& vector_to_fill);

};

template <typename T>
class PostOrderTraversal : public ITraversalStrategy<T>
{
public:

	PostOrderTraversal(const AddCondition& add_condition = AddCondition::SAME_DATA);

	void search(TINode<T>* root, const T& data, std::vector<TINode<T>*>& vector_to_fill);

};

template <typename T>
class BFSTraversal : public ITraversalStrategy<T>
{
public:

	BFSTraversal(const AddCondition& add_condition = AddCondition::SAME_DATA);

	void search(TINode<T>* root, const T& data, std::vector<TINode<T>*>& vector_to_fill);

private:

	std::queue<TINode<T>*> queue;

};

#include "INode.h"

template <typename T>
ITraversalStrategy<T>::ITraversalStrategy(const AddCondition& add_condition)
:
m_add_condition(add_condition)
{
}

template<typename T>
void ITraversalStrategy<T>::add(TINode<T>* root,
								const T& data,
								std::vector<TINode<T>*>& vector_to_fill)
{
	if (m_add_condition == AddCondition::SAME_DATA) {
		if (root->getData() == data) {
			vector_to_fill.push_back(root);
		}
	}
	else if (m_add_condition == AddCondition::NO_CONDITION) {
		vector_to_fill.push_back(root);
	}
	
}

template<typename T>
void ITraversalStrategy<T>::traverse(TINode<T>* root, std::vector<TINode<T>*>& vector_to_fill)
{
	// VERY BAD BUT WORKS
	T* not_used = nullptr;
	search(root, *not_used, vector_to_fill);
}

template<typename T>
PreOrderTraversal<T>::PreOrderTraversal(const AddCondition& add_condition)
:
ITraversalStrategy(add_condition)
{
}

template<typename T>
void PreOrderTraversal<T>::search(TINode<T>* root, 
								  const T& data, 
								  std::vector<TINode<T>*>& vector_to_fill)
{
	assert(root != nullptr);

	this->add(root, data, vector_to_fill);

	std::vector<TINode<T>*> sons = root->getSons();

	for (auto& son : sons) {
		search(son, data, vector_to_fill);
	}
}

template<typename T>
InOrderTraversal<T>::InOrderTraversal(const AddCondition& add_condition)
:
ITraversalStrategy(add_condition)
{
}

template<typename T>
void InOrderTraversal<T>::search(TINode<T>* root, 
								 const T& data, 
								 std::vector<TINode<T>*>& vector_to_fill)
{
	assert(root != nullptr);

	std::vector<TINode<T>*> sons = root->getSons();

	if (!sons.empty()) {
		for (auto& son : sons) {
			search(son, data, vector_to_fill);

			this->add(root, data, vector_to_fill);
		}
	}
	else {
		this->add(root, data, vector_to_fill);
	}
	
}

template<typename T>
PostOrderTraversal<T>::PostOrderTraversal(const AddCondition& add_condition)
:
ITraversalStrategy(add_condition)
{
}

template<typename T>
void PostOrderTraversal<T>::search(TINode<T>* root, 
								   const T& data, 
								   std::vector<TINode<T>*>& vector_to_fill)
{
	assert(root != nullptr);

	std::vector<TINode<T>*> sons = root->getSons();

	for (auto& son : sons) {
		search(son, data, vector_to_fill);
	}

	this->add(root, data, vector_to_fill);
}

template<typename T>
BFSTraversal<T>::BFSTraversal(const AddCondition& add_condition)
:
ITraversalStrategy(add_condition)
{
}

template<typename T>
void BFSTraversal<T>::search(TINode<T>* root, 
							 const T& data, 
							 std::vector<TINode<T>*>& vector_to_fill)
{
	assert(root != nullptr);

	this->add(root, data, vector_to_fill);

	std::vector<TINode<T>*> sons = root->getSons();

	for (auto& son : sons) {
		queue.push(son);
	}

	while (!queue.empty()) {
		TINode<T>* first_in_queue = queue.front();
		queue.pop();
		search(first_in_queue, data, vector_to_fill);
	}
}
