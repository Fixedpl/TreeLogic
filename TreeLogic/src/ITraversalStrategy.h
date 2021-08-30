#pragma once
#include <cassert>
#include <queue>


template <typename T>
class INode;

enum class AddCondition { NO_CONDITION, SAME_DATA };

template <typename T>
class ITraversalStrategy
{
protected:

	void add(INode<T>* root, 
			 const T& data, 
			 std::vector<INode<T>*>& vector_to_fill, 
			 const AddCondition& add_condition);

public:

	virtual void search(INode<T>* root, const T& data, std::vector<INode<T>*>& vector_to_fill,
					    const AddCondition& add_condition = AddCondition::SAME_DATA) = 0;

	void traverse(INode<T>* root, std::vector<INode<T>*>& vector_to_fill);

};

template <typename T>
class PreOrderTraversal : public ITraversalStrategy<T>
{
public:

	void search(INode<T>* root, const T& data, std::vector<INode<T>*>& vector_to_fill,
		const AddCondition& add_condition = AddCondition::SAME_DATA);

};

template <typename T>
class InOrderTraversal : public ITraversalStrategy<T>
{
public:

	void search(INode<T>* root, const T& data, std::vector<INode<T>*>& vector_to_fill,
		const AddCondition& add_condition = AddCondition::SAME_DATA);

};

template <typename T>
class PostOrderTraversal : public ITraversalStrategy<T>
{
public:

	void search(INode<T>* root, const T& data, std::vector<INode<T>*>& vector_to_fill,
		const AddCondition& add_condition = AddCondition::SAME_DATA);

};

template <typename T>
class BFSTraversal : public ITraversalStrategy<T>
{
private:

	std::queue<INode<T>*> queue;

public:	

	void search(INode<T>* root, const T& data, std::vector<INode<T>*>& vector_to_fill,
		const AddCondition& add_condition = AddCondition::SAME_DATA);
	
};

#include "INode.h"

template<typename T>
void ITraversalStrategy<T>::add(INode<T>* root,
								const T& data,
								std::vector<INode<T>*>& vector_to_fill,
								const AddCondition& add_condition)
{
	if (add_condition == AddCondition::SAME_DATA) {
		if (root->getData() == data) {
			vector_to_fill.push_back(root);
		}
	}
	else if (add_condition == AddCondition::NO_CONDITION) {
		vector_to_fill.push_back(root);
	}
	
}

template<typename T>
void ITraversalStrategy<T>::traverse(INode<T>* root, std::vector<INode<T>*>& vector_to_fill)
{
	// VERY BAD BUT WORKS
	T* not_used = nullptr;
	search(root, *not_used, vector_to_fill, AddCondition::NO_CONDITION);
}

template<typename T>
void PreOrderTraversal<T>::search(INode<T>* root, 
								  const T& data, 
								  std::vector<INode<T>*>& vector_to_fill,
								  const AddCondition& add_condition)
{
	assert(root != nullptr);

	this->add(root, data, vector_to_fill, add_condition);

	std::vector<INode<T>*> sons = root->getSons();

	for (auto& son : sons) {
		search(son, data, vector_to_fill, add_condition);
	}
}

template<typename T>
void InOrderTraversal<T>::search(INode<T>* root, 
								 const T& data, 
								 std::vector<INode<T>*>& vector_to_fill,
								 const AddCondition& add_condition)
{
	assert(root != nullptr);

	std::vector<INode<T>*> sons = root->getSons();

	if (!sons.empty()) {
		for (auto& son : sons) {
			search(son, data, vector_to_fill, add_condition);

			this->add(root, data, vector_to_fill, add_condition);
		}
	}
	else {
		this->add(root, data, vector_to_fill, add_condition);
	}
	
}

template<typename T>
void PostOrderTraversal<T>::search(INode<T>* root, 
								   const T& data, 
								   std::vector<INode<T>*>& vector_to_fill,
								   const AddCondition& add_condition)
{
	assert(root != nullptr);

	std::vector<INode<T>*> sons = root->getSons();

	for (auto& son : sons) {
		search(son, data, vector_to_fill, add_condition);
	}

	this->add(root, data, vector_to_fill, add_condition);
}

template<typename T>
void BFSTraversal<T>::search(INode<T>* root, 
							 const T& data, 
							 std::vector<INode<T>*>& vector_to_fill,
							 const AddCondition& add_condition)
{
	assert(root != nullptr);

	this->add(root, data, vector_to_fill, add_condition);

	std::vector<INode<T>*> sons = root->getSons();

	for (auto& son : sons) {
		queue.push(son);
	}

	while (!queue.empty()) {
		INode<T>* first_in_queue = queue.front();
		queue.pop();
		search(first_in_queue, data, vector_to_fill, add_condition);
	}
}
